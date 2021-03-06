/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_CHROME_BROWSER_COMPONENT_UPDATER_TLS_DEPRECATION_CONFIG_COMPONENT_INSTALLER_H_
#define HUHI_CHROMIUM_SRC_CHROME_BROWSER_COMPONENT_UPDATER_TLS_DEPRECATION_CONFIG_COMPONENT_INSTALLER_H_

#define ReconfigureAfterNetworkRestart            \
  ReconfigureAfterNetworkRestart_ChromiumImpl();  \
  static void ReconfigureAfterNetworkRestart
#include "../../../../../chrome/browser/component_updater/tls_deprecation_config_component_installer.h"
#undef ReconfigureAfterNetworkRestart

#endif  // HUHI_CHROMIUM_SRC_CHROME_BROWSER_COMPONENT_UPDATER_TLS_DEPRECATION_CONFIG_COMPONENT_INSTALLER_H_
