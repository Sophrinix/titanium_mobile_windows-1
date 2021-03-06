/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "File.hpp"
#include "Titanium/detail/TiBase.hpp"
#include <algorithm>
#include <iostream>
#include <objbase.h>
#include <ppltasks.h>
#include <collection.h>
#include "Blob.hpp"
#include <boost/algorithm/string/replace.hpp>

using namespace Windows::Storage;
using namespace Windows::Foundation::Collections;
using namespace concurrency;

namespace TitaniumWindows
{
	namespace Filesystem
	{
		File::File(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Titanium::Filesystem::File(js_context)
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Filesystem::File::ctor");
		}

		std::string File::normalizePath(const std::string& path)
		{
			// this assumes we already joined the arguments with separator
			std::string name = static_cast<std::string>(path);
			// Convert "/" to "\\"
			std::replace(name.begin(), name.end(), '/', '\\');
			// remove duplicate separators!
			boost::algorithm::replace_all(name, "\\\\", "\\");
			return name;
		}

		void File::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) {
			// TODO: if argument is empty, we assumes it's called from initializer.
			if (arguments.empty()) {
				return;
			}

			TITANIUM_ASSERT(arguments.size() > 0);
			TITANIUM_ASSERT(arguments.at(0).IsString());

			// this assumes we already joined the arguments with separator
			std::string name = normalizePath(static_cast<std::string>(arguments.at(0)));

			const auto location = Windows::ApplicationModel::Package::Current->InstalledLocation->Path;
			// if this path is relative path, let's use application installed location path
			if (name.find(":\\") == std::string::npos) {
				path_ = TitaniumWindows::Utility::ConvertString(location) + "\\" + name;
			} else {
				path_ = name;
			}

			name_ = name;

			file_ = getFileFromPathSync(path_);
			if (file_ == nullptr) {
				folder_ = getFolderFromPathSync(path_);
			}
		}

		File::~File()
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::Filesystem::File::dtor");
		}

		void File::JSExportInitialize()
		{
			JSExport<File>::SetClassVersion(1);
			JSExport<File>::SetParent(JSExport<Titanium::Filesystem::File>::Class());
		}

		// Creates a directory at the path identified by this file object.
		bool File::createDirectory(const std::string& path)
		{
			auto separator = path.find_last_of("\\");
			const auto parent = path.substr(0, separator);
			const auto desiredName = path.substr(separator + 1);

			const auto folder = getFolderFromPathSync(parent);

			bool result = false;
			concurrency::event event;
			task<StorageFolder^>(folder->CreateFolderAsync(TitaniumWindows::Utility::ConvertString(desiredName))).then([&result, &event](task<StorageFolder^> task) {
					try {
						task.get();
						result = true;
					} catch (Platform::COMException^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					}
					event.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			return result;
		}

		FileProperties::BasicProperties^ File::getStorageProperties(IStorageItem^ file) const
		{
			try {
				if (file == nullptr) {
					return nullptr;
				}
				FileProperties::BasicProperties^ properties = nullptr;
				concurrency::event event;
				task<FileProperties::BasicProperties^>(file->GetBasicPropertiesAsync()).then([&properties, &event](task<FileProperties::BasicProperties^> task) {
						try {
							properties = task.get();
						}
						catch (Platform::COMException^ ex) {
							TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
						}
						event.set();
					},
					concurrency::task_continuation_context::use_arbitrary());
				event.wait();

				return properties;
			} catch (Platform::COMException^ ex) {
				TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
				return nullptr;
			}
		}

		Windows::Storage::StorageFolder^ File::getFolderFromPathSync(Platform::String^ filename) const
		{
			Windows::Storage::StorageFolder^ storageFolder = nullptr;
			concurrency::event event;
			task<StorageFolder^>(Windows::Storage::StorageFolder::GetFolderFromPathAsync(filename)).then([&storageFolder, &event](task<StorageFolder^> task) {
					try {
						storageFolder = task.get();
					}
					catch (Platform::COMException^ ex) {
						storageFolder = nullptr;
					}
					event.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			return storageFolder;
		}

		Windows::Storage::StorageFile^ File::getFileFromPathSync(Platform::String^ filename) const
		{
			Windows::Storage::StorageFile^ storageFile = nullptr;
			concurrency::event event;
			task<StorageFile^>(Windows::Storage::StorageFile::GetFileFromPathAsync(filename)).then([&storageFile, &event](task<StorageFile^> task) {
					try {
						storageFile = task.get();
					}
					catch (Platform::COMException^ ex) {
						storageFile = nullptr;
					}
					event.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			return storageFile;
		}

		bool File::get_executable() const TITANIUM_NOEXCEPT
		{
			// Just return false here because Windows Runtime API doesn't
			// provide a way to get executable attribute
			return false;
		}

		bool File::get_hidden() const TITANIUM_NOEXCEPT
		{
			auto item = getStorageItem();
			if (item == nullptr) {
				return false;
			}
			using namespace Windows::Storage;
			return ((item->Attributes & FileAttributes::Normal) != FileAttributes::Normal);
		}

		std::string File::get_name() const TITANIUM_NOEXCEPT
		{
			return name_;
		}

		std::string File::get_nativePath() const TITANIUM_NOEXCEPT
		{
			return path_;
		}

		std::shared_ptr<Titanium::Filesystem::File> File::get_parent() const TITANIUM_NOEXCEPT
		{
			const std::string path = path_;
			const std::string parent = path.substr(0, path.find_last_of("\\"));

			auto File = get_context().CreateObject(JSExport<Titanium::Filesystem::File>::Class());
			return File.CallAsConstructor(parent).GetPrivate<Titanium::Filesystem::File>();
		}

		bool File::get_readonly() const TITANIUM_NOEXCEPT
		{
			auto item = getStorageItem();
			if (item == nullptr) {
				return false;
			}
			using namespace Windows::Storage;
			return ((item->Attributes & FileAttributes::ReadOnly) == FileAttributes::ReadOnly);
		}

		bool File::get_remoteBackup() const TITANIUM_NOEXCEPT
		{
			return false;
		}

		bool File::get_symbolicLink() const TITANIUM_NOEXCEPT
		{
			return false;
		}

		bool File::get_writable() const TITANIUM_NOEXCEPT
		{
			auto item = getStorageItem();
			if (item == nullptr) {
				return false;
			}
			using namespace Windows::Storage;
			return ((item->Attributes & FileAttributes::ReadOnly) != FileAttributes::ReadOnly);
		}

		unsigned long long File::get_size() const TITANIUM_NOEXCEPT
		{
			const auto prop = getStorageProperties(getStorageItem());
			if (prop == nullptr) {
				return 0;
			} else {
				return prop->Size;
			}
		}

		bool File::append(const std::string& data) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::append(string): Unimplemented");
			return false;
		}

		bool File::append(const std::shared_ptr<Titanium::Blob>& data) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::append(Blob): Unimplemented");
			return false;
		}

		bool File::append(const std::shared_ptr<Titanium::Filesystem::File>& data) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::append(File): Unimplemented");
			return false;
		}

		bool File::copy(const std::string& destinationPath) TITANIUM_NOEXCEPT
		{
			// copy will never work for folder
			if (isFolder()) {
				return false;
			}
			// FIXME Need to normalize the path like we do in constructor!
			auto path = normalizePath(destinationPath);
			auto fileToReplace = this->getFileFromPathSync(path);

			// if destination file is not found, create new file and try again
			if (fileToReplace == nullptr) {
				const bool created = createEmptyFile(path);
				if (created) {
					fileToReplace = getFileFromPathSync(path);
				} else {
					return false;
				}
			}

			concurrency::event event;
			bool result = false;
			create_task(file_->CopyAndReplaceAsync(fileToReplace)).then([&result, &event](task<void> task) {
					try {
						task.get();
						result = true;
					}
					catch (Platform::COMException^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					}
					event.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			return result;
		}

		bool File::createDirectory() TITANIUM_NOEXCEPT
		{
			const bool result = createDirectory(path_);
			if (result) {
				// because this creates new directory which didn't exit, update the folder_ member
				folder_ = getFolderFromPathSync(path_);
				file_ = nullptr;
			}
			return result;
		}

		bool File::createFile() TITANIUM_NOEXCEPT
		{
			const bool result = createEmptyFile(path_);
			if (result) {
				// because this creates new file which didn't exist, update the
				// file_ member
				file_ = getFileFromPathSync(TitaniumWindows::Utility::ConvertString(path_));
				folder_ = nullptr;
			}
			return result;
		}

		std::chrono::milliseconds File::createTimestamp() TITANIUM_NOEXCEPT
		{
			auto item = getStorageItem();
			if (item == nullptr) {
				return std::chrono::milliseconds(0);
			} else {
				return TitaniumWindows::Utility::GetMSecSinceEpoch(item->DateCreated);
			}
		}

		bool File::deleteDirectory(const bool& recursive) TITANIUM_NOEXCEPT
		{
			if (!isFolder()) {
				return false;
			}

			if (!recursive) {
				return deleteFile();
			}

			std::vector<std::string> contents = getDirectoryListing();
			for (size_t i = 0; i < contents.size(); i++) {
				auto value = contents.at(i);
				// FIXME We need to get handles on the sub-folders/files!
				//auto native_file = static_cast<JSObject>(value).GetPrivate<Titanium::Filesystem::File>();
				//if (native_file->isDirectory()) {
				//	if (!native_file->deleteDirectory(recursive)) {
				//		return false;
				//	}
				//} else {
				//	if (!native_file->deleteFile()) {
				//		return false;
				//	}
				//}
			}

			return deleteFile();
		}

		bool File::deleteFile() TITANIUM_NOEXCEPT
		{
			auto item = getStorageItem();
			if (item == nullptr) {
				return false;
			}

			bool result = false;
			concurrency::event event;
			create_task(item->DeleteAsync()).then([&result, &event](task<void> task) {
				try {
					task.get();
					result = true;
				}
				catch (Platform::COMException^ ex) {
					TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
				}
				event.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			event.wait();
			// release the file object because file is deleted
			if (result) {
				file_ = nullptr;
				folder_ = nullptr;
			}
			return result;
		}

		bool File::exists() TITANIUM_NOEXCEPT
		{
			return (getStorageItem() != nullptr);
		}

		std::string File::extension() TITANIUM_NOEXCEPT
		{
			const std::string path = path_;
			return path.substr(path.find_last_of(".") + 1);
		}

		std::vector<std::string> File::getDirectoryListing() TITANIUM_NOEXCEPT
		{
			std::vector<std::string> filenames;
			if (isFile() || !exists()) {
				return filenames;
			}

			// Get folders in folder
			concurrency::event folderEvent;
			create_task(folder_->GetFoldersAsync()).then([&filenames, &folderEvent](task<IVectorView<StorageFolder^>^> task) {
					try {
						auto folders = task.get();
						std::for_each(begin(folders), end(folders), [&filenames](StorageFolder^ folder) {
							filenames.push_back(TitaniumWindows::Utility::ConvertString(folder->Name));
						});
					}
					catch (Platform::COMException^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					}
					folderEvent.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			folderEvent.wait();

			// Get files in folder
			concurrency::event fileEvent;
			create_task(folder_->GetFilesAsync()).then([&filenames, &fileEvent](task<IVectorView<StorageFile^>^> task) {
					try {
						auto files = task.get();
						std::for_each(begin(files), end(files), [&filenames](StorageFile^ file) {
							filenames.push_back(TitaniumWindows::Utility::ConvertString(file->Name));
						});
					}
					catch (Platform::COMException^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					}
					fileEvent.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			fileEvent.wait();

			return filenames;
		}

		bool File::isDirectory() TITANIUM_NOEXCEPT
		{
			auto item = getStorageItem();
			if (item == nullptr) {
				return false;
			}
			using namespace Windows::Storage;
			return ((item->Attributes & FileAttributes::Directory) == FileAttributes::Directory);
		}

		bool File::isFile() TITANIUM_NOEXCEPT
		{
			auto item = getStorageItem();
			if (item == nullptr) {
				return false;
			}
			using namespace Windows::Storage;
			return ((item->Attributes & FileAttributes::Directory) != FileAttributes::Directory);
		}

		std::chrono::milliseconds File::modificationTimestamp() TITANIUM_NOEXCEPT
		{
			const auto prop = getStorageProperties(getStorageItem());
			if (prop == nullptr) {
				return std::chrono::milliseconds(0);
			} else {
				return TitaniumWindows::Utility::GetMSecSinceEpoch(prop->DateModified);
			}
		}

		bool File::move(const std::string& newpath) TITANIUM_NOEXCEPT
		{
			auto path = normalizePath(newpath);

			// if this item is folder, call rename
			if (isFolder()) {
				return this->rename(path);
			}

			// make sure to create detination file before getting StorageFile
			// otherwise GetFileFromPathSync will return nullptr
			if (!createEmptyFile(path)) {
				return false;
			}

			// retrieve destination file
			StorageFile^ fileToReplace = getFileFromPathSync(TitaniumWindows::Utility::ConvertString(path));

			if (fileToReplace == nullptr) {
				return false;
			}

			bool result = false;
			concurrency::event event;
			create_task(this->file_->MoveAndReplaceAsync(fileToReplace)).then([&result, &event](task<void> task) {
					try {
						task.get();
						result = true;
					}
					catch (Platform::COMException^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					}
					event.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			// release the file object because file is deleted
			if (result) {
				file_ = nullptr;
				folder_ = nullptr;
			}

			return result;
		}

		std::shared_ptr<Titanium::Filesystem::FileStream> File::open(const std::unordered_set<Titanium::Filesystem::MODE>&) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("File::open: Unimplemented");
			return nullptr;
		}

		std::shared_ptr<Titanium::Blob> File::read() TITANIUM_NOEXCEPT
		{
			if (file_ == nullptr) {
				return nullptr;
			}
			auto Blob = get_context().CreateObject(JSExport<TitaniumWindows::Blob>::Class());
			auto blob = Blob.CallAsConstructor();
			auto blob_ptr = blob.GetPrivate<TitaniumWindows::Blob>();

			blob_ptr->construct(file_);

			return blob.GetPrivate<Titanium::Blob>();
		}

		bool File::rename(const std::string& desiredName) TITANIUM_NOEXCEPT
		{
			auto path = normalizePath(desiredName);
			auto item = getStorageItem();
			concurrency::event event;
			bool result = false;
			create_task(item->RenameAsync(TitaniumWindows::Utility::ConvertString(path))).then([&result, &event](task<void> task) {
					try {
						task.get();
						result = true;
					}
					catch (Platform::COMException^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					}
					event.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			return result;
		}

		std::string File::resolve() TITANIUM_NOEXCEPT
		{
			return path_;
		}

		unsigned long long File::spaceAvailable() TITANIUM_NOEXCEPT
		{
			const auto prop = getStorageProperties(getStorageItem());
			const auto propertiesName = ref new Platform::Collections::Vector<Platform::String^>();
			propertiesName->Append("System.FreeSpace");
			uint64 freeSpace;
			concurrency::event event;
			task<IMap<Platform::String^, Platform::Object^>^>(prop->RetrievePropertiesAsync(propertiesName)).then([&freeSpace, &event](task<IMap<Platform::String^, Platform::Object^>^> task) {
					try {
						const auto extraProperties = task.get();
						freeSpace = (uint64)extraProperties->Lookup("System.FreeSpace");
					}
					catch (Platform::COMException^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					}
					event.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();
			return freeSpace;
		}

		bool File::prepareWrite() 
		{
			// if this item represents folder, write will never work
			if (isFolder()) {
				TITANIUM_LOG_WARN("File::write: Can't write to directory");
				return false;
			}

			if (file_ == nullptr) {
				// create empty file, then retrieve StorageFile object
				if (!createEmptyFile(path_)) {
					TITANIUM_LOG_WARN("File::write: Can't write to file");
					return false;
				}
				file_ = getFileFromPathSync(TitaniumWindows::Utility::ConvertString(path_));
				if (file_ == nullptr) {
					TITANIUM_LOG_WARN("File::write: Can't get file");
					return false;
				}
			}
			return true;
		}

		bool File::write(const std::string& data, const bool& append) TITANIUM_NOEXCEPT
		{
			if (!prepareWrite()) {
				return false;
			}

			return write(getBufferFromString(data, append, file_));
		}

		bool File::write(const std::shared_ptr<Titanium::Blob>& data, const bool& append) TITANIUM_NOEXCEPT
		{
			if (!prepareWrite()) {
				return false;
			}

			if (data->get_size() > 0) {
				return write(getBufferFromBytes(&data->getData()[0], data->get_size(), append, file_));
			} else {
				return write(ref new Streams::Buffer(0));
			}
		}

		bool File::write(const std::shared_ptr<Titanium::Filesystem::File>& data, const bool& append) TITANIUM_NOEXCEPT
		{
			if (!prepareWrite()) {
				return false;
			}

			auto content = data->getContent();
			if (content.size() > 0) {
				return write(getBufferFromBytes(&content[0], content.size(), append, file_));
			} else {
				return write(ref new Streams::Buffer(0));
			}
		}

		bool File::write(Streams::IBuffer^ buffer)
		{
			if (buffer == nullptr) {
				TITANIUM_LOG_DEBUG("Can't get content from Ti.Filesystem.File.write(content)");
				return false;
			}

			bool result = false;
			concurrency::event event;
			task<void>(FileIO::WriteBufferAsync(file_, buffer)).then([&result, &event](task<void> task) {
					try {
						task.get();
						result = true;
					} catch (Platform::COMException^ ex) {
						TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
					}
					event.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			return result;
		}

		std::vector<std::uint8_t> File::getContent() const TITANIUM_NOEXCEPT
		{
			return TitaniumWindows::Utility::GetContentFromFile(file_);
		}


	} // namespace Filesystem
} // namespace TitaniumWindows
