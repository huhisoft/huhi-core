// Copyright 2020 The Huhi Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/renderer_context_menu/render_view_context_menu.h"

#include "huhi/browser/autocomplete/huhi_autocomplete_scheme_classifier.h"
#include "huhi/browser/profiles/profile_util.h"
#include "huhi/browser/renderer_context_menu/huhi_spelling_options_submenu_observer.h"
#include "huhi/browser/translate/buildflags/buildflags.h"
#include "huhi/components/tor/buildflags/buildflags.h"
#include "chrome/browser/autocomplete/chrome_autocomplete_provider_client.h"
#include "components/omnibox/browser/autocomplete_classifier.h"
#include "components/omnibox/browser/autocomplete_controller.h"

#if BUILDFLAG(ENABLE_TOR)
#include "huhi/browser/tor/tor_profile_service_factory.h"
#endif

// Our .h file creates a masquerade for RenderViewContextMenu.  Switch
// back to the Chromium one for the Chromium implementation.
#undef RenderViewContextMenu
#define RenderViewContextMenu RenderViewContextMenu_Chromium

namespace {

GURL GetSelectionNavigationURL(Profile* profile, const base::string16& text) {
  AutocompleteMatch match;
  AutocompleteClassifier classifier(
      std::make_unique<AutocompleteController>(
          std::make_unique<ChromeAutocompleteProviderClient>(profile),
          AutocompleteClassifier::DefaultOmniboxProviders()),
      std::make_unique<HuhiAutocompleteSchemeClassifier>(profile));
  classifier.Classify(text, false, false,
                      metrics::OmniboxEventProto::INVALID_SPEC, &match, NULL);
  classifier.Shutdown();
  return match.destination_url;
}

}  // namespace

#define HUHI_APPEND_SEARCH_PROVIDER \
  if (GetProfile()->IsOffTheRecord()) { \
    selection_navigation_url_ = \
        GetSelectionNavigationURL(GetProfile(), params_.selection_text); \
    if (!selection_navigation_url_.is_valid()) \
      return; \
  }

// Use our subclass to initialize SpellingOptionsSubMenuObserver.
#define SpellingOptionsSubMenuObserver HuhiSpellingOptionsSubMenuObserver

#include "../../../../../chrome/browser/renderer_context_menu/render_view_context_menu.cc"

#undef SpellingOptionsSubMenuObserver

// Make it clear which class we mean here.
#undef RenderViewContextMenu
#undef HUHI_APPEND_SEARCH_PROVIDER

HuhiRenderViewContextMenu::HuhiRenderViewContextMenu(
    content::RenderFrameHost* render_frame_host,
    const content::ContextMenuParams& params)
  : RenderViewContextMenu_Chromium(render_frame_host, params) {
}

bool HuhiRenderViewContextMenu::IsCommandIdEnabled(int id) const {
  switch (id) {
    case IDC_CONTENT_CONTEXT_OPENLINKTOR:
#if BUILDFLAG(ENABLE_TOR)
      if (huhi::IsTorDisabledForProfile(GetProfile()))
        return false;

      return params_.link_url.is_valid() &&
             IsURLAllowedInIncognito(params_.link_url, browser_context_) &&
             !huhi::IsTorProfile(GetProfile());
#else
      return false;
#endif
    default:
      return RenderViewContextMenu_Chromium::IsCommandIdEnabled(id);
  }
}

void HuhiRenderViewContextMenu::ExecuteCommand(int id, int event_flags) {
  switch (id) {
    case IDC_CONTENT_CONTEXT_OPENLINKTOR:
      profiles::SwitchToTorProfile(
          base::Bind(
              OnProfileCreated, params_.link_url,
              content::Referrer(
                GURL(), network::mojom::ReferrerPolicy::kStrictOrigin)));
      break;
    default:
      RenderViewContextMenu_Chromium::ExecuteCommand(id, event_flags);
  }
}

void HuhiRenderViewContextMenu::AddSpellCheckServiceItem(bool is_checked) {
  // Call our implementation, not the one in the base class.
  // Assumption:
  // Use of spelling service is disabled in Huhi profile preferences.
  DCHECK(!GetProfile()->GetPrefs()->GetBoolean(
      spellcheck::prefs::kSpellCheckUseSpellingService));
  AddSpellCheckServiceItem(&menu_model_, is_checked);
}

// static
void HuhiRenderViewContextMenu::AddSpellCheckServiceItem(
    ui::SimpleMenuModel* menu,
    bool is_checked) {
  // Suppress adding "Spellcheck->Ask Huhi for suggestions" item.
}

void HuhiRenderViewContextMenu::InitMenu() {
  RenderViewContextMenu_Chromium::InitMenu();

#if BUILDFLAG(ENABLE_TOR) || !BUILDFLAG(ENABLE_HUHI_TRANSLATE_GO)
  int index = -1;
#endif
#if BUILDFLAG(ENABLE_TOR)
  // Add Open Link with Tor
  if (!TorProfileServiceFactory::IsTorDisabled() &&
      !params_.link_url.is_empty()) {
    const Browser* browser = GetBrowser();
    const bool is_app = browser && browser->is_type_app();

    index = menu_model_.GetIndexOfCommandId(
        IDC_CONTENT_CONTEXT_OPENLINKOFFTHERECORD);
    DCHECK_NE(index, -1);

    menu_model_.InsertItemWithStringIdAt(
        index + 1,
        IDC_CONTENT_CONTEXT_OPENLINKTOR,
        is_app ? IDS_CONTENT_CONTEXT_OPENLINKTOR_INAPP
               : IDS_CONTENT_CONTEXT_OPENLINKTOR);
  }
#endif

  // Only show the translate item when go-translate is enabled.
#if !BUILDFLAG(ENABLE_HUHI_TRANSLATE_GO)
  index = menu_model_.GetIndexOfCommandId(IDC_CONTENT_CONTEXT_TRANSLATE);
  if (index != -1)
    menu_model_.RemoveItemAt(index);
#endif
}
