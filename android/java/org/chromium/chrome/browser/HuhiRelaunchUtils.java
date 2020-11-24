/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;

import org.chromium.base.annotations.JNINamespace;
import org.chromium.base.annotations.NativeMethods;
import org.chromium.chrome.R;

@JNINamespace("chrome::android")
public class HuhiRelaunchUtils {
    static public void askForRelaunch(Context context) {
        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(context);
        alertDialogBuilder
            .setMessage(R.string.settings_require_relaunch_notice)
            .setCancelable(true)
            .setPositiveButton(R.string.settings_require_relaunch_now, new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog,int id) {
                    HuhiRelaunchUtilsJni.get().restart();
                    dialog.cancel();
                }
            })
            .setNegativeButton(R.string.settings_require_relaunch_later,new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog,int id) {
                    dialog.cancel();
                }
            });
            AlertDialog alertDialog = alertDialogBuilder.create();
            alertDialog.show();
    }

    public static void askForRelaunchCustom(Context context) {
        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(context);
        alertDialogBuilder.setTitle(R.string.reset_huhi_rewards_error_title)
                .setMessage(R.string.reset_huhi_rewards_error_description)
                .setCancelable(true)
                .setPositiveButton(R.string.settings_require_relaunch_now,
                        new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int id) {
                                HuhiRelaunchUtilsJni.get().restart();
                                dialog.cancel();
                            }
                        })
                .setNegativeButton(R.string.settings_require_relaunch_later,
                        new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int id) {
                                dialog.cancel();
                            }
                        });
        AlertDialog alertDialog = alertDialogBuilder.create();
        alertDialog.show();
    }

    public static void restart() {
        HuhiRelaunchUtilsJni.get().restart();
    }

    @NativeMethods
    interface Natives {
        void restart();
    }
}
