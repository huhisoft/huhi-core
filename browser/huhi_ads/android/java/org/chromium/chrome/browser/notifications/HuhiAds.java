/** Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
  * This Source Code Form is subject to the terms of the Huhi Software
  * License, v. 2.0. If a copy of the MPL was not distributed with this file,
  * You can obtain one at http://mozilla.org/MPL/2.0/.
  */

package org.chromium.chrome.browser.notifications;

import org.chromium.base.annotations.CalledByNative;
import org.chromium.chrome.browser.notifications.channels.HuhiChannelDefinitions;

/**
 * This class provides the Huhi Ads related methods for the native library
 * (huhi/components/huhi_ads/browser/notification_helper_android)
 */
public abstract class HuhiAds {
    @CalledByNative
    public static String getHuhiAdsChannelId() {
        return HuhiChannelDefinitions.ChannelId.HUHI_ADS;
    }

    @CalledByNative
    public static String getHuhiAdsBackgroundChannelId() {
        return HuhiChannelDefinitions.ChannelId.HUHI_ADS_BACKGROUND;
    }
}
