/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Window.hpp"

namespace Titanium
{
	namespace UI
	{
		Window::Window(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : View(js_context),
		      openWindowParams_ctor__(js_context.CreateObject(JSExport<Titanium::UI::OpenWindowParams>::Class())),
		      closeWindowParams_ctor__(js_context.CreateObject(JSExport<Titanium::UI::CloseWindowParams>::Class())),
		      barColor__(""),
		      exitOnClose__(false),
		      extendEdges__({EXTEND_EDGE::NONE}),
		      fullscreen__(false),
		      hideShadow__(false),
		      modal__(false),
		      navBarHidden__(false),
		      navTintColor__(""),
		      orientationModes__(),
		      theme__(""),
		      translucent__(false)
		{
			TITANIUM_LOG_DEBUG("Window:: ctor ", this);
		}

		Window::~Window() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("Window:: dtor ", this);
		}

		void Window::close(const std::shared_ptr<CloseWindowParams>& params) const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::close: Unimplemented");
		}

		void Window::open(const std::shared_ptr<OpenWindowParams>& params) const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::open: Unimplemented");
		}

		bool Window::get_exitOnClose() const TITANIUM_NOEXCEPT
		{
			return exitOnClose__;
		}

		void Window::set_exitOnClose(const bool& exitOnClose) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_exitOnClose: Unimplemented");
			exitOnClose__ = exitOnClose;
		}

		std::unordered_set<EXTEND_EDGE> Window::get_extendEdges() const TITANIUM_NOEXCEPT
		{
			return extendEdges__;
		}

		void Window::set_extendEdges(const std::unordered_set<EXTEND_EDGE>& extendEdges) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_extendEdges: Unimplemented");
		}

		bool Window::get_fullscreen() const TITANIUM_NOEXCEPT
		{
			return fullscreen__;
		}

		void Window::set_fullscreen(const bool& fullscreen) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_fullscreen: Unimplemented");
			fullscreen__ = fullscreen;
		}

		bool Window::get_hideShadow() const TITANIUM_NOEXCEPT
		{
			return hideShadow__;
		}

		void Window::set_hideShadow(const bool& hideShadow) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_hideShadow: Unimplemented");
			hideShadow__ = hideShadow;
		}

		bool Window::get_modal() const TITANIUM_NOEXCEPT
		{
			return modal__;
		}

		void Window::set_modal(const bool& modal) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_modal: Unimplemented");
			modal__ = modal;
		}

		bool Window::get_navBarHidden() const TITANIUM_NOEXCEPT
		{
			return navBarHidden__;
		}

		void Window::set_navBarHidden(const bool& navBarHidden) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_navBarHidden: Unimplemented");
			navBarHidden__ = navBarHidden;
		}

		std::string Window::get_navTintColor() const TITANIUM_NOEXCEPT
		{
			return navTintColor__;
		}

		void Window::set_navTintColor(const std::string &navTintColor) TITANIUM_NOEXCEPT
		{
			navTintColor__ = navTintColor;
		}

		std::vector<ORIENTATION> Window::get_orientationModes() const TITANIUM_NOEXCEPT
		{
			return orientationModes__;
		}

		void Window::set_orientationModes(const std::vector<ORIENTATION>& orientationModes) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_orientationModes: Unimplemented");
		}

		std::string Window::get_theme() const TITANIUM_NOEXCEPT
		{
			return theme__;
		}

		void Window::set_theme(const std::string& theme) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_theme: Unimplemented");
			theme__ = theme;
		}

		TitleAttributesParams Window::get_titleAttributes() const TITANIUM_NOEXCEPT
		{
			return titleAttributes__;
		}

		void Window::set_titleAttributes(const TitleAttributesParams& titleAttributes) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_titleAttributes: Unimplemented");
			titleAttributes__ = titleAttributes;
		}

		bool Window::get_translucent() const TITANIUM_NOEXCEPT
		{
			return translucent__;
		}

		void Window::set_translucent(const bool& translucent) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Window::set_translucent: Unimplemented");
			translucent__ = translucent;
		}

		std::string Window::get_barColor() const TITANIUM_NOEXCEPT 
		{
			return barColor__;
		}
		void Window::set_barColor(const std::string& barColor) TITANIUM_NOEXCEPT 
		{
			barColor__ = barColor;
		}

		void Window::JSExportInitialize()
		{
			JSExport<Window>::SetClassVersion(1);
			JSExport<Window>::SetParent(JSExport<View>::Class());
			JSExport<Window>::AddFunctionProperty("close", std::mem_fn(&Window::js_close));
			JSExport<Window>::AddFunctionProperty("open", std::mem_fn(&Window::js_open));
			JSExport<Window>::AddValueProperty("barColor", std::mem_fn(&Window::js_get_barColor), std::mem_fn(&Window::js_set_barColor));
			JSExport<Window>::AddValueProperty("exitOnClose", std::mem_fn(&Window::js_get_exitOnClose), std::mem_fn(&Window::js_set_exitOnClose));
			JSExport<Window>::AddValueProperty("extendEdges", std::mem_fn(&Window::js_get_extendEdges), std::mem_fn(&Window::js_set_extendEdges));
			JSExport<Window>::AddValueProperty("fullscreen", std::mem_fn(&Window::js_get_fullscreen), std::mem_fn(&Window::js_set_fullscreen));
			JSExport<Window>::AddValueProperty("hideShadow", std::mem_fn(&Window::js_get_hideShadow), std::mem_fn(&Window::js_set_hideShadow));
			JSExport<Window>::AddValueProperty("modal", std::mem_fn(&Window::js_get_modal), std::mem_fn(&Window::js_set_modal));
			JSExport<Window>::AddValueProperty("navBarHidden", std::mem_fn(&Window::js_get_navBarHidden), std::mem_fn(&Window::js_set_navBarHidden));
			JSExport<Window>::AddValueProperty("navTintColor", std::mem_fn(&Window::js_get_navTintColor), std::mem_fn(&Window::js_set_navTintColor));
			JSExport<Window>::AddValueProperty("orientationModes", std::mem_fn(&Window::js_get_orientationModes), std::mem_fn(&Window::js_set_orientationModes));
			JSExport<Window>::AddValueProperty("theme", std::mem_fn(&Window::js_get_theme), std::mem_fn(&Window::js_set_theme));
			JSExport<Window>::AddValueProperty("titleAttributes", std::mem_fn(&Window::js_get_titleAttributes), std::mem_fn(&Window::js_set_titleAttributes));
			JSExport<Window>::AddValueProperty("translucent", std::mem_fn(&Window::js_get_translucent), std::mem_fn(&Window::js_set_translucent));
		}

		JSValue Window::js_close(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			auto js_context = this_object.get_context();
			auto params = js_context.CreateObject();
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());

				params = closeWindowParams_ctor__.CallAsConstructor({_0});
			}


			close(params.GetPrivate<CloseWindowParams>());
			return get_context().CreateUndefined();
		}

		JSValue Window::js_open(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			auto js_context = this_object.get_context();
			auto params = js_context.CreateObject();
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());

				params = openWindowParams_ctor__.CallAsConstructor({_0});
			}

			open(params.GetPrivate<OpenWindowParams>());
			return get_context().CreateUndefined();
		}

		JSValue Window::js_get_barColor() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_barColor());
		}

		bool Window::js_set_barColor(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_barColor(static_cast<std::string>(argument));
			return true;
		}

		JSValue Window::js_get_exitOnClose() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(exitOnClose__);
		}

		bool Window::js_set_exitOnClose(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_exitOnClose(static_cast<bool>(argument));
			return true;
		}

		JSValue Window::js_get_extendEdges() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(Constants::to_underlying_type(extendEdges__));
		}

		bool Window::js_set_extendEdges(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			extendEdges__ = Constants::to_EXTEND_EDGE(static_cast<std::underlying_type<EXTEND_EDGE>::type>(argument));
			set_extendEdges(extendEdges__);
			return true;
		}

		JSValue Window::js_get_fullscreen() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(fullscreen__);
		}

		bool Window::js_set_fullscreen(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_fullscreen(static_cast<bool>(argument));
			return true;
		}

		JSValue Window::js_get_hideShadow() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(hideShadow__);
		}

		bool Window::js_set_hideShadow(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_hideShadow(static_cast<bool>(argument));
			return true;
		}

		JSValue Window::js_get_modal() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(modal__);
		}

		bool Window::js_set_modal(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_modal(static_cast<bool>(argument));
			return true;
		}

		JSValue Window::js_get_navBarHidden() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(navBarHidden__);
		}

		bool Window::js_set_navBarHidden(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_navBarHidden(static_cast<bool>(argument));
			return true;
		}

		JSValue Window::js_get_navTintColor() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(navTintColor__);
		}

		bool Window::js_set_navTintColor(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_navTintColor(static_cast<std::string>(argument));
			return true;
		}

		JSValue Window::js_get_orientationModes() const TITANIUM_NOEXCEPT
		{
			std::vector<JSValue> modes;
			for (auto mode : orientationModes__) {
				modes.push_back(get_context().CreateNumber(Constants::to_underlying_type(mode)));
			}
			return get_context().CreateArray(modes);
		}

		bool Window::js_set_orientationModes(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsObject());
			auto js_arg = static_cast<JSObject>(argument);
			TITANIUM_ASSERT(js_arg.IsArray());
			auto modes = static_cast<JSArray>(js_arg);
			auto js_modes= static_cast<std::vector<JSValue>>(modes);
			std::vector<ORIENTATION> orientationModes;
			for (auto mode : js_modes) {
				orientationModes.push_back(Constants::to_ORIENTATION(static_cast<std::underlying_type<ORIENTATION>::type>(mode)));
			}
			set_orientationModes(orientationModes);

			return true;
		}

		JSValue Window::js_get_theme() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(theme__);
		}

		bool Window::js_set_theme(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_theme(static_cast<std::string>(argument));
			return true;
		}

		JSValue Window::js_get_titleAttributes() const TITANIUM_NOEXCEPT
		{
			return TitleAttributesParams_to_js(get_context(), titleAttributes__);
		}

		bool Window::js_set_titleAttributes(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_titleAttributes(js_to_TitleAttributesParams(static_cast<JSObject>(argument)));
			return true;
		}

		JSValue Window::js_get_translucent() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(translucent__);
		}

		bool Window::js_set_translucent(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_translucent(static_cast<bool>(argument));
			return true;
		}
	} // namespace UI
}  // namespace Titanium
