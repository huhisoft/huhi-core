/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import { bindActionCreators } from 'redux'
import { connect } from 'react-redux'
import * as shieldsPanelActions from '../actions/shieldsPanelActions'
import * as settingsActions from '../actions/settingsActions'
import * as shieldsPanelState from '../state/shieldsPanelState'
import HuhiShields from '../containers/huhiShields'
import { State } from '../types/state/mainState'

const mapStateToProps = (
  state: State,
  ownProps: {
    settings: chrome.huhiShields.HuhiShieldsViewPreferences
  }
) => {
  return ({
    shieldsPanelTabData: shieldsPanelState.getActiveTabData(state.shieldsPanel),
    persistentData: shieldsPanelState.getPersistentData(state.shieldsPanel),
    settingsData: shieldsPanelState.mergeSettingsData(state.shieldsPanel, ownProps.settings)
  })
}

// combine all actions used outside background pages.
// for background action bindings, refer to background/index.js
const actions = Object.assign({}, shieldsPanelActions, settingsActions)

const mapDispatchToProps = (dispatch: any) => ({
  actions: bindActionCreators(actions, dispatch)
})

export default connect(
  mapStateToProps,
  mapDispatchToProps
)(HuhiShields as any) // TODO remove any
