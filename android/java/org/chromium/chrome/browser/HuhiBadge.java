/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser;

import android.app.Activity;
import android.content.Context;
import android.util.AttributeSet;
import android.view.View;
import android.widget.TextView;

import org.chromium.chrome.R;

public class HuhiBadge extends TextView {
  /**
   * Update by using the following
   * HuhiBadge.update(this, HuhiBadge.BadgeType.REWARDS, 77);
   * HuhiBadge.update(this, HuhiBadge.BadgeType.SHIELDS, 88);
   */

    public enum BadgeType {
        SHIELDS("shields"),
        REWARDS("rewards");

        private final String type;

        /**
         * @param text
         */
        BadgeType(final String type) {
            this.type = type;
        }

        /* (non-Javadoc)
         * @see java.lang.Enum#toString()
         */
        @Override
        public String toString() {
            return type;
        }
    }

    public HuhiBadge(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public void update(int counter) {
        this.bringToFront();

        //Manage min value
        if (counter == 0) {
            this.setVisibility(View.GONE);
        } else {
            this.setVisibility(View.VISIBLE);
            this.setText(String.valueOf(counter));
        }
    }

    /**
     * update the given menu item with badgeCount
     */
    public static void update(final Activity activity, BadgeType badgeType, int counter) {
        HuhiBadge toShow;
        HuhiBadge toHide;

        // Set Color
        //if (badgeType == BadgeType.SHIELDS) {
            if (counter < 10) {
              toShow = (HuhiBadge) activity.findViewById(R.id.huhi_shields_badge_small);
              toHide = (HuhiBadge) activity.findViewById(R.id.huhi_shields_badge_large);
            } else {
              toShow = (HuhiBadge) activity.findViewById(R.id.huhi_shields_badge_large);
              toHide = (HuhiBadge) activity.findViewById(R.id.huhi_shields_badge_small);
            }
        // } else {
        //     if (counter < 10) {
        //       toShow = (HuhiBadge) activity.findViewById(R.id.huhi_rewards_badge_small);
        //       toHide = (HuhiBadge) activity.findViewById(R.id.huhi_rewards_badge_large);
        //     } else {
        //       toShow = (HuhiBadge) activity.findViewById(R.id.huhi_rewards_badge_large);
        //       toHide = (HuhiBadge) activity.findViewById(R.id.huhi_rewards_badge_small);
        //     }
        // }

        toHide.update(0);
        toShow.update(counter);
    }
}
