/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.base;

import androidx.annotation.Nullable;
import android.content.SharedPreferences;

import org.chromium.base.ContextUtils;
import org.chromium.base.supplier.Supplier;

public abstract class HuhiCommandLineInitUtil {
    // Duplicate constant to avoid pull dependancy into base
    private static final String PREF_QA_VLOG_REWARDS = "qa_vlog_rewards";

    public static void initCommandLine(String fileName) {
        String[] args = null;
        SharedPreferences sharedPreferences = ContextUtils.getAppSharedPreferences();
        if (sharedPreferences.getBoolean(PREF_QA_VLOG_REWARDS, false)) {
            args = new String[2];
            args[0] = "--enable-logging=stderr";
            args[1] = "--vmodule=*/bat-native-ads/*=6,*/huhi_ads/*=6,*/huhi_user_model/*=6,*/bat_ads/*=6,*/bat-native-ledger/*=6,*/huhi_rewards/*=6";
        }
        CommandLine.init(args == null ? null : args);
    }

    public static void initCommandLine(
            String fileName, @Nullable Supplier<Boolean> shouldUseDebugFlags) {
        initCommandLine(fileName);
    }
}
