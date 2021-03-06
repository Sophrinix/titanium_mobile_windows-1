/**
 * TitaniumKit
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeWindowExample.hpp"
#include "NativeViewExample.hpp"

NativeWindowExample::NativeWindowExample(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::UI::Window(js_context)
{
	TITANIUM_LOG_DEBUG("NativeWindowExample:: ctor ", this);
}

NativeWindowExample::~NativeWindowExample() TITANIUM_NOEXCEPT
{
	TITANIUM_LOG_DEBUG("NativeWindowExample:: dtor ", this);
}

void NativeWindowExample::open(const std::shared_ptr<Titanium::UI::OpenWindowParams>& params) const TITANIUM_NOEXCEPT
{
	TITANIUM_LOG_DEBUG("NativeWindowExample::open");
	for (auto native_view_ptr : layoutDelegate__->get_children()) {
		auto view_ptr = std::dynamic_pointer_cast<NativeViewExample>(native_view_ptr);
		TITANIUM_LOG_DEBUG("NativeWindowExample::open: add child ", view_ptr);
	}
}

void NativeWindowExample::JSExportInitialize()
{
	JSExport<NativeWindowExample>::SetClassVersion(1);
	JSExport<NativeWindowExample>::SetParent(JSExport<Titanium::UI::Window>::Class());
}
