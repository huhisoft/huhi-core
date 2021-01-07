/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.shields;

/**
 * Allows monitoring of huhi shields menu actions.
 */
public interface HuhiShieldsMenuObserver {
	/**
	 * Informs when the any of HuhiShields Menu switch changes.
	 * @param isOn Whether shield is on.
	 * @param isTopShield Whether it is a top shield or not.
	 */
	public void onMenuTopShieldsChanged(boolean isOn, boolean isTopShield);
}
