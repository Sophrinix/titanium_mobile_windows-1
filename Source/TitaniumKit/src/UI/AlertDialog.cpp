/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/AlertDialog.hpp"

namespace Titanium
{
	namespace UI
	{
		AlertDialog::AlertDialog(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Module(js_context),
			  cancel__(-1),
		      message__(js_context.CreateString()),
		      title__(js_context.CreateString())
		{
			TITANIUM_LOG_DEBUG("AlertDialog:: ctor ", this);
		}

		AlertDialog::~AlertDialog() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("AlertDialog:: dtor ", this);
		}

		void AlertDialog::hide() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("AlertDialog::hide");
		}

		void AlertDialog::show() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("AlertDialog::show");
		}

		std::vector<std::string> AlertDialog::get_buttonNames() const TITANIUM_NOEXCEPT
		{
			return buttonNames__;
		}

		void AlertDialog::set_buttonNames(const std::vector<std::string>& buttonNames) TITANIUM_NOEXCEPT
		{
			buttonNames__ = buttonNames;
		}

		void AlertDialog::addButton(const std::string& buttonName) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("AlertDialog::addButton not implemented");
		}

		int32_t AlertDialog::get_cancel() const TITANIUM_NOEXCEPT
		{
			return cancel__;
		}

		void AlertDialog::set_cancel(const int32_t& cancel) TITANIUM_NOEXCEPT
		{
			cancel__ = cancel;
		}

		std::string AlertDialog::get_message() const TITANIUM_NOEXCEPT
		{
			return message__;
		}

		void AlertDialog::set_message(const std::string& message) TITANIUM_NOEXCEPT
		{
			message__ = message;
		}

		std::string AlertDialog::get_title() const TITANIUM_NOEXCEPT
		{
			return title__;
		}

		void AlertDialog::set_title(const std::string& title) TITANIUM_NOEXCEPT
		{
			title__ = title;
		}

		void AlertDialog::JSExportInitialize()
		{
			JSExport<AlertDialog>::SetClassVersion(1);
			JSExport<AlertDialog>::SetParent(JSExport<Module>::Class());
			JSExport<AlertDialog>::AddFunctionProperty("hide", std::mem_fn(&AlertDialog::js_hide));
			JSExport<AlertDialog>::AddFunctionProperty("show", std::mem_fn(&AlertDialog::js_show));
			JSExport<AlertDialog>::AddValueProperty("buttonNames", std::mem_fn(&AlertDialog::js_get_buttonNames), std::mem_fn(&AlertDialog::js_set_buttonNames));
			JSExport<AlertDialog>::AddValueProperty("cancel", std::mem_fn(&AlertDialog::js_get_cancel), std::mem_fn(&AlertDialog::js_set_cancel));
			JSExport<AlertDialog>::AddValueProperty("message", std::mem_fn(&AlertDialog::js_get_message), std::mem_fn(&AlertDialog::js_set_message));
			JSExport<AlertDialog>::AddValueProperty("title", std::mem_fn(&AlertDialog::js_get_title), std::mem_fn(&AlertDialog::js_set_title));
		}

		JSValue AlertDialog::js_hide(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 0);
			hide();
			return get_context().CreateUndefined();
		}

		JSValue AlertDialog::js_show(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.size() == 0);
			show();
			return get_context().CreateUndefined();
		}

		JSValue AlertDialog::js_get_buttonNames() const TITANIUM_NOEXCEPT
		{
			auto context = get_context();
			std::vector<JSValue> jsButtonNames = std::vector<JSValue>();
			for (auto &buttonName : buttonNames__) {
				jsButtonNames.push_back(context.CreateString(buttonName));
			}
			return context.CreateArray(jsButtonNames);
		}

		bool AlertDialog::js_set_buttonNames(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsObject());
			auto object = static_cast<JSObject>(argument);

			// This allows us to see the size of the array
			const auto string_count = object.GetPropertyNames().GetCount();
			if (string_count == 0) {
				TITANIUM_LOG_WARN("AlertDialog::js_set_buttonNames no button names given");
				return false;
			}

			// convert the array into std::vector
			buttonNames__ = std::vector<std::string>();
			for (unsigned i = 0; i < string_count; ++i) {
				// TODO verify that the array has something at this index, JS arrays can be sparse!
				JSValue button_name = object.GetProperty(i);

				// Precondition
				TITANIUM_ASSERT(button_name.IsString());
				std::string name = static_cast<std::string>(button_name);
				buttonNames__.push_back(name);
				addButton(name);
			}
			return true;
		}

		JSValue AlertDialog::js_get_message() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_message());
		}

		bool AlertDialog::js_set_message(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_message(static_cast<std::string>(argument));
			return true;
		}

			JSValue AlertDialog::js_get_cancel() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(get_cancel());
		}

			bool AlertDialog::js_set_cancel(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_cancel(static_cast<int32_t>(argument));
			return true;
		}

		JSValue AlertDialog::js_get_title() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_title());
		}

		bool AlertDialog::js_set_title(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_title(static_cast<std::string>(argument));
			return true;
		}
	} // namespace UI
}  // namespace Titanium
