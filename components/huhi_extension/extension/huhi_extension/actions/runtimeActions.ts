/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as types from '../constants/runtimeActionTypes'

export function runtimeDidStartup () {
  return {
    type: types.RUNTIME_DID_STARTUP
  }
}
