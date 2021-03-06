/**
 * TitaniumKit Titanium.UI.ListView
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_LISTVIEW_HPP_
#define _TITANIUM_UI_LISTVIEW_HPP_

#include "Titanium/UI/View.hpp"
#include "Titanium/UI/ListSection.hpp"
#include "Titanium/UI/ListViewAnimationProperties.hpp"
#include "Titanium/UI/ListViewMarkerProps.hpp"
#include <vector>
#include <unordered_map>

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;
		using ListSection_shared_ptr_t = std::shared_ptr<ListSection>;
		using View_shared_ptr_t = std::shared_ptr<View>;
		
		/*!
		  @class
		  @discussion This is the Titanium.UI.ListView Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.ListView
		*/
		class TITANIUMKIT_EXPORT ListView : public View, public JSExport<ListView>
		{

		public:

			/*!
			  @property
			  @abstract sections
			  @discussion Sections of this list.
			*/
			virtual std::vector<ListSection_shared_ptr_t> get_sections() const TITANIUM_NOEXCEPT;
			virtual void set_sections(const std::vector<ListSection_shared_ptr_t>& sections) TITANIUM_NOEXCEPT;

			template<typename T>
			std::vector<std::shared_ptr<T>> createSectionViewAt(uint32_t index)
			{
				// lazy loading
				loadJS();
				
				std::vector<std::shared_ptr<T>> items;
				const std::vector<JSValue> args { get_object(), sections__.at(index)->get_object() };
				JSValue result = sectionViewCreateFunction__(args, ti_listview_exports__);
				TITANIUM_ASSERT(result.IsObject());
				auto js_items = static_cast<JSObject>(result);
				TITANIUM_ASSERT(js_items.IsArray());
				
				const auto length = static_cast<uint32_t>(js_items.GetProperty("length"));
				for (uint32_t i = 0; i < length; i++) {
					items.push_back(static_cast<JSObject>(js_items.GetProperty(i)).GetPrivate<T>());
				}
				
				return items;
			}

			/*!
			  @property
			  @abstract footerTitle
			  @discussion List view footer title.
			*/
			virtual std::string get_footerTitle() const TITANIUM_NOEXCEPT;
			virtual void set_footerTitle(const std::string& footerTitle) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract headerTitle
			  @discussion List view header title.
			*/
			virtual std::string get_headerTitle() const TITANIUM_NOEXCEPT;
			virtual void set_headerTitle(const std::string& headerTitle) TITANIUM_NOEXCEPT;
			
			/*!
			 @property
			 @abstract footerView
			 @discussion List view footer as a view that will be rendered instead of a label.
			 */
			virtual View_shared_ptr_t get_footerView() const TITANIUM_NOEXCEPT;
			virtual void set_footerView(const View_shared_ptr_t& value) TITANIUM_NOEXCEPT;
			
			/*!
			 @property
			 @abstract headerView
			 @discussion List view header as a view that will be rendered instead of a label.
			 */
			virtual View_shared_ptr_t get_headerView() const TITANIUM_NOEXCEPT;
			virtual void set_headerView(const View_shared_ptr_t& value) TITANIUM_NOEXCEPT;
			
			/*!
			 @property
			 @abstract searchView
			 @discussion Search field to use for the list view.
			 */
			virtual View_shared_ptr_t get_searchView() const TITANIUM_NOEXCEPT;
			virtual void set_searchView(const View_shared_ptr_t& value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract searchText
			  @discussion The string to use as the search parameter.
			*/
			virtual std::string get_searchText() const TITANIUM_NOEXCEPT;
			virtual void set_searchText(const std::string& searchText) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract caseInsensitiveSearch
			  @discussion Determines if the search performed is case insensitive.
			*/
			virtual bool get_caseInsensitiveSearch() const TITANIUM_NOEXCEPT;
			virtual void set_caseInsensitiveSearch(bool value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract sectionCount
			  @discussion Number of sections in this list view.
			*/
			virtual uint32_t get_sectionCount() const TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract showVerticalScrollIndicator
			  @discussion Determines whether this list view displays a vertical scroll indicator.
			*/
			virtual bool get_showVerticalScrollIndicator() const TITANIUM_NOEXCEPT;
			virtual void set_showVerticalScrollIndicator(bool value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract separatorColor
			  @discussion Separator line color between rows, as a color name or hex triplet.
			*/
			virtual std::string get_separatorColor() const TITANIUM_NOEXCEPT;
			virtual void set_separatorColor(std::string value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract defaultItemTemplate
			  @discussion Sets the default template for list data items that do not specify the `template` property.
			*/
			virtual std::string get_defaultItemTemplate() const TITANIUM_NOEXCEPT;
			virtual void set_defaultItemTemplate(std::string value) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract scrollToItem
			  @discussion Scrolls to a specific item.
			*/
			virtual void scrollToItem(uint32_t sectionIndex, uint32_t itemIndex, const std::shared_ptr<ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract appendSection
			  @discussion Appends a single section or an array of sections to the end of the list.
			*/
			virtual void appendSection(const std::vector<ListSection_shared_ptr_t>& section, const std::shared_ptr<ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract deleteSectionAt
			  @discussion Deletes an existing section.
			*/
			virtual void deleteSectionAt(uint32_t sectionIndex, const std::shared_ptr<ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract insertSectionAt
			  @discussion Inserts a section or an array of sections at a specific index.
			*/
			virtual void insertSectionAt(uint32_t sectionIndex, const std::vector<ListSection_shared_ptr_t>& section, const std::shared_ptr<ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract replaceSectionAt
			  @discussion Replaces an existing section.
			*/
			virtual void replaceSectionAt(uint32_t sectionIndex, const std::vector<ListSection_shared_ptr_t>& section, const std::shared_ptr<ListViewAnimationProperties>& animation) TITANIUM_NOEXCEPT;

			/*!
			  @method
			  @abstract setMarker
			  @discussion Sets a reference item in the list view.
			*/
			virtual void setMarker(const ListViewMarkerProps& marker) TITANIUM_NOEXCEPT;

			ListView(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ListView() = default;
			ListView(const ListView&) = default;
			ListView& operator=(const ListView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ListView(ListView&&)                 = default;
			ListView& operator=(ListView&&)      = default;
#endif

			static void JSExportInitialize();

			virtual JSValue js_get_sections() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_sections(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_footerTitle() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_footerTitle(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_headerTitle() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_headerTitle(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_searchText() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_searchText(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_footerView() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_footerView(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_headerView() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_headerView(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_searchView() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_searchView(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_caseInsensitiveSearch() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_caseInsensitiveSearch(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_sectionCount() const TITANIUM_NOEXCEPT final; // read only
			virtual JSValue js_get_showVerticalScrollIndicator() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_showVerticalScrollIndicator(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_separatorColor() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_separatorColor(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_defaultItemTemplate() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_defaultItemTemplate(const JSValue& argument) TITANIUM_NOEXCEPT final;

			virtual JSValue js_scrollToItem(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_appendSection(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_deleteSectionAt(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_insertSectionAt(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_replaceSectionAt(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setMarker(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getTemplates(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setTemplates(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getSections(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setSections(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getFooterTitle(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setFooterTitle(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getFooterView(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setFooterView(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getHeaderTitle(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setHeaderTitle(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getHeaderView(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setHeaderView(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getSearchView(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setSearchView(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getSearchText(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setSearchText(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getCaseInsensitiveSearch(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setCaseInsensitiveSearch(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getSectionCount(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getShowVerticalScrollIndicator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setShowVerticalScrollIndicator(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getSeparatorColor(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setSeparatorColor(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getDefaultItemTemplate(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setDefaultItemTemplate(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

			void loadJS();

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::vector<ListSection_shared_ptr_t> sections__;
			std::string footerTitle__;
			std::string headerTitle__;
			View_shared_ptr_t footerView__;
			View_shared_ptr_t headerView__;
			View_shared_ptr_t searchView__;
			std::string searchText__;
			bool caseInsensitiveSearch__ { false };
			bool showVerticalScrollIndicator__;
			std::string separatorColor__;
			std::string defaultItemTemplate__;
			ListViewMarkerProps marker__;

			JSObject ti_listview_exports__;
			JSObject sectionViewCreateFunction__;
			JSObject listviewAnimationProperties_ctor__;
#pragma warning(pop)
		};
	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_UI_LISTVIEW_HPP_