/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/content_settings/core/browser/huhi_content_settings_ephemeral_provider.h"
#include "huhi/components/content_settings/core/browser/huhi_content_settings_pref_provider.h"

#define EphemeralProvider HuhiEphemeralProvider
#define PrefProvider HuhiPrefProvider
#include "../../../../../../components/content_settings/core/browser/host_content_settings_map.cc"
#undef EphemeralProvider
#undef PrefProvider
