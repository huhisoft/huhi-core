// Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

// Redux API
import { createStore, applyMiddleware } from 'redux'

// Thunk for async actions
import thunk from 'redux-thunk'

// Feature core reducer
import { mainNewTabReducer } from './reducers'

export default createStore(mainNewTabReducer, applyMiddleware(thunk))
