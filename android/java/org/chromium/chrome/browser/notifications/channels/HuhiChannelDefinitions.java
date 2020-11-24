/**
 * Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.notifications.channels;

import android.app.NotificationManager;

import org.chromium.chrome.R;
import org.chromium.components.browser_ui.notifications.channels.ChannelDefinitions;
import org.chromium.components.browser_ui.notifications.channels.ChannelDefinitions.PredefinedChannel;

import java.util.Map;
import java.util.Set;

public class HuhiChannelDefinitions {
    public class ChannelId {
        public static final String HUHI_ADS = "com.huhi.browser.ads";
        public static final String HUHI_ADS_BACKGROUND = "com.huhi.browser.ads.background";
        public static final String HUHI_BROWSER = "com.huhi.browser";
    }

    public class ChannelGroupId {
        public static final String HUHI_ADS = "com.huhi.browser.ads";
    }

    static protected void addHuhiChannels(
        Map<String, PredefinedChannel> map, Set<String> startup) {
        map.put(ChannelId.HUHI_ADS,
                PredefinedChannel.create(ChannelId.HUHI_ADS,
                                         R.string.notification_category_huhi_ads,
                                         NotificationManager.IMPORTANCE_HIGH, ChannelGroupId.HUHI_ADS));
        startup.add(ChannelId.HUHI_ADS);

        map.put(ChannelId.HUHI_ADS_BACKGROUND,
                PredefinedChannel.create(ChannelId.HUHI_ADS_BACKGROUND,
                                         R.string.notification_category_huhi_ads_background,
                                         NotificationManager.IMPORTANCE_LOW, ChannelGroupId.HUHI_ADS));
        startup.add(ChannelId.HUHI_ADS_BACKGROUND);
    }

    static protected void addHuhiChannelGroups(
        Map<String, ChannelDefinitions.PredefinedChannelGroup> map) {
        map.put(ChannelGroupId.HUHI_ADS,
                new ChannelDefinitions.PredefinedChannelGroup(
                    ChannelGroupId.HUHI_ADS, R.string.notification_category_group_huhi_ads));
    }
}
