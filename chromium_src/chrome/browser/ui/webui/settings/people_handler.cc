/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// IsSetupInProgress isn't accurate in huhi sync flow especially for the first
// time setup, we rely on it to display setup dialog
#define HUHI_GET_SYNC_STATUS_DICTIONARY  \
  sync_status->SetBoolean(                \
      "firstSetupInProgress",             \
      service && !disallowed_by_policy && \
          !service->GetUserSettings()->IsFirstSetupComplete());

#include "../../../../../../../chrome/browser/ui/webui/settings/people_handler.cc"
#undef HUHI_GET_SYNC_STATUS_DICTIONARY
