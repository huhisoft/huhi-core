/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/extensions/huhi_theme_event_router.h"

#include <memory>
#include <string>
#include <utility>

#include "huhi/browser/themes/huhi_dark_mode_utils.h"
#include "huhi/common/extensions/api/huhi_theme.h"
#include "chrome/browser/profiles/profile.h"
#include "extensions/browser/event_router.h"
#include "ui/native_theme/native_theme.h"

namespace extensions {

HuhiThemeEventRouter::HuhiThemeEventRouter(Profile* profile)
    : profile_(profile),
      observer_(this) {
  observer_.Add(ui::NativeTheme::GetInstanceForNativeUi());
}

HuhiThemeEventRouter::~HuhiThemeEventRouter() {}

void HuhiThemeEventRouter::OnNativeThemeUpdated(
    ui::NativeTheme* observed_theme) {
  DCHECK(observer_.IsObserving(observed_theme));
  Notify();
}

void HuhiThemeEventRouter::Notify() {
  const std::string theme_type =
      dark_mode::GetStringFromHuhiDarkModeType(
          dark_mode::GetActiveHuhiDarkModeType());

  auto event = std::make_unique<extensions::Event>(
      extensions::events::HUHI_ON_HUHI_THEME_TYPE_CHANGED,
      api::huhi_theme::OnHuhiThemeTypeChanged::kEventName,
      api::huhi_theme::OnHuhiThemeTypeChanged::Create(theme_type),
      profile_);

  if (EventRouter* event_router = EventRouter::Get(profile_))
    event_router->BroadcastEvent(std::move(event));
}

}  // namespace extensions
