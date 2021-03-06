/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import store from '../../../huhi_extension/extension/huhi_extension/background/store'
import { initialState } from '../../testData'

describe('store test', () => {
  it('store can get state', () => {
    expect(store.getState()).toEqual(initialState)
  })
})
