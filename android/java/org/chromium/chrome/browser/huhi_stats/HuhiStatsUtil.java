/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.huhi_stats;

import android.util.Pair;

import org.chromium.chrome.browser.app.HuhiActivity;
import org.chromium.chrome.browser.huhi_stats.HuhiStatsBottomSheetDialogFragment;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class HuhiStatsUtil {
	/*
	* Gets string view of specific time in seconds for Huhi stats
	*/
	public static String getHuhiStatsStringFromTime(long seconds) {
		String result = "";
		if (seconds > 24 * 60 * 60) {
			result = result + (seconds / (24 * 60 * 60)) + "d";
		} else if (seconds > 60 * 60) {
			result = result + (seconds / (60 * 60)) + "h";
		} else if (seconds > 60) {
			result = result + (seconds / 60) + "m";
		} else {
			result = result + seconds + "s";
		}
		return result;
	}

	public static Pair<String, String> getHuhiStatsStringFormNumberPair(long number, boolean isBytes) {
		String result = "";
		String suffix = isBytes ? "KB" : "" ;
		long base = isBytes ? 1024L : 1000L;
		if (number >= base * base * base) {
			result = result + (number / (base * base * base));
			number = number % (base * base * base);
			result = result + "." + (number / (10L * base * base));
			suffix = isBytes ? "GB" : "B";
		} else if (number >= (10L * base * base) && number < (base * base * base)) {
			result = result + (number / (base * base));
			suffix = isBytes ? "MB" : "M";
		} else if (number >= (base * base) && number < (10L * base * base)) {
			result = result + (number / (base * base));
			number = number % (base * base);
			result = result + "." + (number / (100L * base));
			suffix = isBytes ? "MB" : "M";
		} else if (number >= (10L * base) && number < (base * base)) {
			result = result + (number / base);
			suffix = isBytes ? "KB" : "K";
		} else if (number >= base && number < (10L * base)) {
			result = result + (number / base);
			number = number % base;
			result = result + "." + (number / 100L);
			suffix = isBytes ? "KB" : "K";
		} else {
			result = result + number;
		}
		return new Pair<>(result, suffix);
	}

	public static void showHuhiStats() {
		if (HuhiActivity.getHuhiActivity() != null) {
			HuhiStatsBottomSheetDialogFragment huhiStatsBottomSheetDialogFragment = HuhiStatsBottomSheetDialogFragment.newInstance();
			huhiStatsBottomSheetDialogFragment.show(HuhiActivity.getHuhiActivity().getSupportFragmentManager(), HuhiStatsBottomSheetDialogFragment.TAG_FRAGMENT);
		}
	}

	public static String getCalculatedDate(String dateFormat, int days) {
		Calendar cal = Calendar.getInstance();
		SimpleDateFormat s = new SimpleDateFormat(dateFormat);
		cal.add(Calendar.DAY_OF_YEAR, days);
		return s.format(new Date(cal.getTimeInMillis()));
	}
}