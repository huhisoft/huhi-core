/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_MOJOM_H_
#define BAT_ADS_MOJOM_H_

#include "bat/ads/public/interfaces/ads_database.mojom.h"
#include "bat/ads/public/interfaces/ads.mojom.h"

namespace ads {

using Environment = mojom::HuhiAdsEnvironment;

using BuildChannel = mojom::HuhiAdsBuildChannel;
using BuildChannelPtr = mojom::HuhiAdsBuildChannelPtr;

using AdNotificationEventType = mojom::HuhiAdsAdNotificationEventType;

using UrlRequest = mojom::HuhiAdsUrlRequest;
using UrlRequestPtr = mojom::HuhiAdsUrlRequestPtr;
using UrlRequestMethod = mojom::HuhiAdsUrlRequestMethod;

using UrlResponse = mojom::HuhiAdsUrlResponse;
using UrlResponsePtr = mojom::HuhiAdsUrlResponsePtr;

using DBCommand = ads_database::mojom::DBCommand;
using DBCommandPtr = ads_database::mojom::DBCommandPtr;
using DBCommandBinding = ads_database::mojom::DBCommandBinding;
using DBCommandBindingPtr = ads_database::mojom::DBCommandBindingPtr;
using DBCommandResult = ads_database::mojom::DBCommandResult;
using DBCommandResultPtr = ads_database::mojom::DBCommandResultPtr;
using DBCommandResponse = ads_database::mojom::DBCommandResponse;
using DBCommandResponsePtr = ads_database::mojom::DBCommandResponsePtr;
using DBRecord = ads_database::mojom::DBRecord;
using DBRecordPtr = ads_database::mojom::DBRecordPtr;
using DBTransaction = ads_database::mojom::DBTransaction;
using DBTransactionPtr = ads_database::mojom::DBTransactionPtr;
using DBValue = ads_database::mojom::DBValue;
using DBValuePtr = ads_database::mojom::DBValuePtr;

}  // namespace ads

#endif  // BAT_ADS_MOJOM_H_
