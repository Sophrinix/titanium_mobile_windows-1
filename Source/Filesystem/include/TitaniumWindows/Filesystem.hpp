/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_FILESYSTEMMODULE_HPP_
#define _TITANIUMWINDOWS_FILESYSTEMMODULE_HPP_

#include "TitaniumWindows/detail/FilesystemBase.hpp"

namespace TitaniumWindows {

  using namespace JavaScriptCoreCPP;

  /*!
    @class

    @discussion This is the Titanium.FilesystemModule implementation for Windows.
    */
  class TITANIUMWINDOWS_FILESYSTEM_EXPORT FilesystemModule final : public Titanium::FilesystemModule, public JSExport <FilesystemModule> {

  public:

    FilesystemModule(const JSContext& js_context) TITANIUM_NOEXCEPT;
    FilesystemModule(const FilesystemModule&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

    virtual ~FilesystemModule();
    FilesystemModule(const FilesystemModule&)            = default;
    FilesystemModule& operator=(const FilesystemModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    FilesystemModule(FilesystemModule&&)                 = default;
    FilesystemModule& operator=(FilesystemModule&&)      = default;
#endif

    static void JSExportInitialize();

    virtual JSValue createTempDirectory() TITANIUM_NOEXCEPT;
    virtual JSValue createTempFile() TITANIUM_NOEXCEPT;
    virtual bool isExternalStoragePresent() TITANIUM_NOEXCEPT;
    virtual JSValue openStream(std::unordered_set<Titanium::Filesystem::MODE> modes, const JSString& path) TITANIUM_NOEXCEPT;

    virtual JSString separator() const TITANIUM_NOEXCEPT;
    virtual JSString applicationCacheDirectory() const TITANIUM_NOEXCEPT;
    virtual JSString applicationDataDirectory() const TITANIUM_NOEXCEPT;
    virtual JSString applicationDirectory() const TITANIUM_NOEXCEPT;
    virtual JSString applicationSupportDirectory() const TITANIUM_NOEXCEPT;
    virtual JSString externalStorageDirectory() const TITANIUM_NOEXCEPT;
    virtual JSString lineEnding() const TITANIUM_NOEXCEPT;
    virtual JSString resourcesDirectory() const TITANIUM_NOEXCEPT;
    virtual JSString tempDirectory() const TITANIUM_NOEXCEPT;
  protected:

  private:
	
  };

}  // namespace TitaniumWindows

#endif // _TITANIUMWINDOWS_FILESYSTEMMODULE_HPP_