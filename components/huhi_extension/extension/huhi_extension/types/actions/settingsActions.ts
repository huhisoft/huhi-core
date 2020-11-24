/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as types from '../../constants/settingsTypes'
import { Settings, SettingsData } from '../other/settingsTypes'

interface SetStoreSettingsChangeReturn {
  type: typeof types.SET_STORE_SETTINGS_CHANGE,
  settingsData: Partial<SettingsData>
}

export interface SetStoreSettingsChange {
  (settingsData: Partial<SettingsData>): SetStoreSettingsChangeReturn
}

export interface SettingsDidChange {
  (settings: Settings): SetStoreSettingsChangeReturn
}

export type settingsActions =
  SetStoreSettingsChangeReturn
