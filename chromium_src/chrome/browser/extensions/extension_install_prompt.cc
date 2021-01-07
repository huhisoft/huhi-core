/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/extensions/extension_install_prompt.h"

#include "huhi/browser/huhi_browser_process_impl.h"
#include "huhi/components/huhi_component_updater/browser/extension_whitelist_service.h"
#include "huhi/grit/huhi_generated_resources.h"
#include "ui/base/l10n/l10n_util.h"

#define GetDialogTitle GetDialogTitle_ChromiumImpl
#include "../../../../../chrome/browser/extensions/extension_install_prompt.cc"
#undef GetDialogTitle

base::string16 ExtensionInstallPrompt::Prompt::GetDialogTitle() const {
  if (!g_huhi_browser_process->extension_whitelist_service()->IsVetted(
          extension())) {
    if (type_ == ExtensionInstallPrompt::INSTALL_PROMPT ||
        type_ == ExtensionInstallPrompt::WEBSTORE_WIDGET_PROMPT) {
      return l10n_util::GetStringUTF16(
          IDS_UNVETTED_EXTENSION_INSTALL_PROMPT_TITLE);
    }
  }
  return GetDialogTitle_ChromiumImpl();
}
