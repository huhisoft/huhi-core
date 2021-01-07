/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// Types
import * as types from '../../../../huhi_extension/extension/huhi_extension/constants/shieldsPanelTypes'
import * as windowTypes from '../../../../huhi_extension/extension/huhi_extension/constants/windowTypes'
import * as tabTypes from '../../../../huhi_extension/extension/huhi_extension/constants/tabTypes'
import * as webNavigationTypes from '../../../../huhi_extension/extension/huhi_extension/constants/webNavigationTypes'
import { State } from '../../../../huhi_extension/extension/huhi_extension/types/state/shieldsPannelState'
import { ShieldDetails } from '../../../../huhi_extension/extension/huhi_extension/types/actions/shieldsPanelActions'

// APIs
import * as shieldsAPI from '../../../../huhi_extension/extension/huhi_extension/background/api/shieldsAPI'
import * as tabsAPI from '../../../../huhi_extension/extension/huhi_extension/background/api/tabsAPI'
import * as browserActionAPI from '../../../../huhi_extension/extension/huhi_extension/background/api/browserActionAPI'

// Reducers
import shieldsPanelReducer from '../../../../huhi_extension/extension/huhi_extension/background/reducers/shieldsPanelReducer'

// State helpers
import * as shieldsPanelState from '../../../../huhi_extension/extension/huhi_extension/state/shieldsPanelState'
import * as noScriptState from '../../../../huhi_extension/extension/huhi_extension/state/noScriptState'

// Utils
import { initialState } from '../../../testData'
import * as deepFreeze from 'deep-freeze-node'
import * as actions from '../../../../huhi_extension/extension/huhi_extension/actions/shieldsPanelActions'

const origin = 'https://hnq.vn'
const windowId = 1
const tabId = 2

const details: ShieldDetails = {
  id: tabId,
  origin,
  hostname: 'hnq.vn',
  httpUpgradableResources: 'block',
  javascript: 'block',
  trackers: 'block',
  ads: 'block',
  cosmeticFiltering: 'block_third_party',
  fingerprinting: 'block',
  cookies: 'block'
}

const tab: chrome.tabs.Tab = {
  active: true,
  id: tabId,
  windowId,
  index: 1,
  pinned: false,
  highlighted: false,
  incognito: false,
  selected: false,
  discarded: false,
  autoDiscardable: false
}

const state: State = deepFreeze({
  persistentData: {
    isFirstAccess: true
  },
  settingsData: {
    showAdvancedView: false,
    statsBadgeVisible: true
  },
  tabs: {
    2: {
      ...details,
      adsBlocked: 0,
      controlsOpen: true,
      huhiShields: 'allow',
      trackersBlocked: 0,
      httpsRedirected: 0,
      javascriptBlocked: 0,
      fingerprintingBlocked: 0,
      noScriptInfo: {},
      adsBlockedResources: [],
      fingerprintingBlockedResources: [],
      httpsRedirectedResources: [],
      trackersBlockedResources: []
    }
  },
  windows: {
    1: 2
  },
  currentWindowId: 1
})

describe('huhiShieldsPanelReducer', () => {
  it('should handle initial state', () => {
    // avoid printing error logs to the test console.
    // this is expected since state is undefined but we want to avoid polluting the test logs
    console.error = () => ''
    expect(shieldsPanelReducer(undefined, actions.allowScriptOriginsOnce()))
      .toEqual(initialState.shieldsPanel)
  })

  describe('ON_COMMITTED', () => {
    let spy: jest.SpyInstance
    let resetNoScriptInfoSpy: jest.SpyInstance
    let resetBlockingResourcesSpy: jest.SpyInstance
    const tabId = 1
    beforeEach(() => {
      spy = jest.spyOn(shieldsPanelState, 'resetBlockingStats')
      resetNoScriptInfoSpy = jest.spyOn(noScriptState, 'resetNoScriptInfo')
      resetBlockingResourcesSpy = jest.spyOn(shieldsPanelState, 'resetBlockingResources')
    })
    afterEach(() => {
      spy.mockRestore()
      resetNoScriptInfoSpy.mockRestore()
      resetBlockingResourcesSpy.mockRestore()
    })
    it('calls resetBlockingStats when isMainFrame is true', () => {
      shieldsPanelReducer(initialState.shieldsPanel, {
        type: webNavigationTypes.ON_COMMITTED,
        tabId: tabId,
        url: 'https://www.hnq.vn',
        isMainFrame: true
      })
      expect(spy).toBeCalledTimes(1)
      expect(spy.mock.calls[0][1]).toBe(tabId)
    })
    it('does not call resetBlockingStats when isMainFrame is false', () => {
      shieldsPanelReducer(initialState.shieldsPanel, {
        type: webNavigationTypes.ON_COMMITTED,
        tabId: tabId,
        url: 'https://www.hnq.vn',
        isMainFrame: false
      })
      expect(spy).not.toBeCalled()
    })
    it('calls resetNoScriptInfo when isMainFrame is true', () => {
      shieldsPanelReducer(initialState.shieldsPanel, {
        type: webNavigationTypes.ON_COMMITTED,
        tabId: tabId,
        url: 'https://www.hnq.vn',
        isMainFrame: true
      })
      expect(resetNoScriptInfoSpy).toBeCalledTimes(1)
      expect(resetNoScriptInfoSpy.mock.calls[0][1]).toBe(tabId)
      expect(resetNoScriptInfoSpy.mock.calls[0][2]).toBe('https://www.hnq.vn')
    })
    it('does not call resetNoScriptInfo when isMainFrame is false', () => {
      shieldsPanelReducer(initialState.shieldsPanel, {
        type: webNavigationTypes.ON_COMMITTED,
        tabId: tabId,
        url: 'https://www.hnq.vn',
        isMainFrame: false
      })
      expect(resetNoScriptInfoSpy).not.toBeCalled()
    })
    it('calls resetBlockingResources when isMainFrame is true', () => {
      shieldsPanelReducer(initialState.shieldsPanel, {
        type: webNavigationTypes.ON_COMMITTED,
        tabId: tabId,
        url: 'https://www.hnq.vn',
        isMainFrame: true
      })
      expect(spy).toBeCalledTimes(1)
      expect(spy.mock.calls[0][1]).toBe(tabId)
    })
    it('does not call resetBlockingResources when isMainFrame is false', () => {
      shieldsPanelReducer(initialState.shieldsPanel, {
        type: webNavigationTypes.ON_COMMITTED,
        tabId: tabId,
        url: 'https://www.hnq.vn',
        isMainFrame: false
      })
      expect(spy).not.toBeCalled()
    })
  })

  describe('WINDOW_REMOVED', () => {
    const windowId = 1
    let spy: jest.SpyInstance
    beforeEach(() => {
      spy = jest.spyOn(shieldsPanelState, 'removeWindowInfo')
    })
    afterEach(() => {
      spy.mockRestore()
    })
    it('calls shieldsPanelState.removeWindowInfo', () => {
      shieldsPanelReducer(initialState.shieldsPanel, {
        type: windowTypes.WINDOW_REMOVED,
        windowId: windowId
      })
      expect(spy).toBeCalledTimes(1)
      expect(spy.mock.calls[0][1]).toBe(windowId)
    })
  })

  describe('WINDOW_FOCUS_CHANGED', () => {
    const windowId = 1
    const tabId = 2
    let updateFocusedWindowSpy: jest.SpyInstance
    let requestShieldPanelDataSpy: jest.SpyInstance
    const state = deepFreeze({
      ...initialState.shieldsPanel,
      windows: {
        1: tabId
      },
      tabs: {
        [tabId]: { url: 'https://hnq.vn' }
      }
    })
    beforeEach(() => {
      updateFocusedWindowSpy = jest.spyOn(shieldsPanelState, 'updateFocusedWindow')
      requestShieldPanelDataSpy = jest.spyOn(shieldsAPI, 'requestShieldPanelData')
    })
    afterEach(() => {
      updateFocusedWindowSpy.mockRestore()
      requestShieldPanelDataSpy.mockRestore()
    })
    it('calls shieldsPanelState.updateFocusedWindow', () => {
      shieldsPanelReducer(state, { type: windowTypes.WINDOW_FOCUS_CHANGED, windowId: windowId })
      expect(updateFocusedWindowSpy).toBeCalledTimes(1)
      expect(updateFocusedWindowSpy.mock.calls[0][1]).toBe(windowId)
    })
    it('calls shieldsPanelState.requestShieldPanelDataSpy ', () => {
      shieldsPanelReducer(state, { type: windowTypes.WINDOW_FOCUS_CHANGED, windowId: windowId })
      expect(requestShieldPanelDataSpy).toBeCalledWith(tabId)
    })
  })

  describe('TAB_DATA_CHANGED', () => {
    let updateActiveTabSpy: jest.SpyInstance
    const state = deepFreeze({ ...initialState.shieldsPanel, windows: { 1: tabId }, tabs: {} })
    beforeEach(() => {
      updateActiveTabSpy = jest.spyOn(shieldsPanelState, 'updateActiveTab')
    })
    afterEach(() => {
      updateActiveTabSpy.mockRestore()
    })
    it('calls shieldsPanelState.updateActiveTab when the tab is active', () => {
      shieldsPanelReducer(state, {
        type: tabTypes.TAB_DATA_CHANGED,
        tabId: tabId,
        tab,
        changeInfo: {}
      })
      expect(updateActiveTabSpy).toBeCalledTimes(1)
      expect(updateActiveTabSpy.mock.calls[0][1]).toBe(windowId)
      expect(updateActiveTabSpy.mock.calls[0][2]).toBe(tabId)
    })
    it('does not call shieldsPanelState.updateActiveTab when the tab is not active', () => {
      shieldsPanelReducer(state, {
        type: tabTypes.TAB_DATA_CHANGED,
        tabId: tabId,
        tab: {
          ...tab,
          active: false
        },
        changeInfo: {}
      })
      expect(updateActiveTabSpy).not.toBeCalled()
    })
  })

  describe('TAB_CREATED', () => {
    const state = {
      ...initialState.shieldsPanel,
      windows: {
        1: tabId
      },
      tabs: {}
    }
    let updateActiveTabSpy: jest.SpyInstance
    beforeEach(() => {
      updateActiveTabSpy = jest.spyOn(shieldsPanelState, 'updateActiveTab')
    })
    afterEach(() => {
      updateActiveTabSpy.mockRestore()
    })
    it('calls shieldsPanelState.updateActiveTab when the tab is active', () => {
      shieldsPanelReducer(state, {
        type: tabTypes.TAB_CREATED,
        tab: {
          ...tab,
          active: true
        }
      })
      expect(updateActiveTabSpy).toBeCalledTimes(1)
      expect(updateActiveTabSpy.mock.calls[0][1]).toBe(windowId)
      expect(updateActiveTabSpy.mock.calls[0][2]).toBe(tabId)
    })
    it('does not call shieldsPanelState.updateActiveTab when the tab is not active', () => {
      shieldsPanelReducer(state, {
        type: tabTypes.TAB_CREATED,
        tab: {
          ...tab,
          active: false
        }
      })
      expect(updateActiveTabSpy).not.toBeCalled()
    })
  })

  describe('SHIELDS_PANEL_DATA_UPDATED', () => {
    it('updates state detail', () => {
      expect(
        shieldsPanelReducer(initialState.shieldsPanel, {
          type: types.SHIELDS_PANEL_DATA_UPDATED,
          details
        })).toEqual({
          ...state,
          currentWindowId: -1,
          windows: {}
        })
    })
  })

  describe('SHIELDS_TOGGLED', () => {
    let reloadTabSpy: jest.SpyInstance
    let setAllowHuhiShieldsSpy: jest.SpyInstance
    beforeEach(() => {
      reloadTabSpy = jest.spyOn(tabsAPI, 'reloadTab')
      setAllowHuhiShieldsSpy = jest.spyOn(shieldsAPI, 'setAllowHuhiShields')
    })
    afterEach(() => {
      reloadTabSpy.mockRestore()
      setAllowHuhiShieldsSpy.mockRestore()
    })
    it('should call setAllowHuhiShields', () => {
      expect(
        shieldsPanelReducer(state, {
          type: types.SHIELDS_TOGGLED,
          setting: 'allow'
        })).toEqual(state)
      expect(setAllowHuhiShieldsSpy).toBeCalledWith(origin, 'allow')
    })
  })

  describe('HTTPS_EVERYWHERE_TOGGLED', () => {
    let reloadTabSpy: jest.SpyInstance
    let setAllowHTTPUpgradableResourcesSpy: jest.SpyInstance
    beforeEach(() => {
      reloadTabSpy = jest.spyOn(tabsAPI, 'reloadTab')
      setAllowHTTPUpgradableResourcesSpy = jest.spyOn(shieldsAPI, 'setAllowHTTPUpgradableResources')
    })
    afterEach(() => {
      reloadTabSpy.mockRestore()
      setAllowHTTPUpgradableResourcesSpy.mockRestore()
    })
    it('should call setAllowHTTPUpgradableResources', () => {
      expect(
        shieldsPanelReducer(state, {
          type: types.HTTPS_EVERYWHERE_TOGGLED,
          setting: 'block'
        })).toEqual(state)
      expect(setAllowHTTPUpgradableResourcesSpy).toBeCalledWith(origin, 'allow')
    })
  })

  describe('JAVASCRIPT_TOGGLED', () => {
    let reloadTabSpy: jest.SpyInstance
    let setAllowJavaScriptSpy: jest.SpyInstance
    beforeEach(() => {
      reloadTabSpy = jest.spyOn(tabsAPI, 'reloadTab')
      setAllowJavaScriptSpy = jest.spyOn(shieldsAPI, 'setAllowJavaScript')
    })
    afterEach(() => {
      reloadTabSpy.mockRestore()
      setAllowJavaScriptSpy.mockRestore()
    })
    it('should call setAllowJavaScript', () => {
      expect(
        shieldsPanelReducer(state, {
          type: types.JAVASCRIPT_TOGGLED,
          setting: 'allow'
        })).toEqual(state)
      expect(setAllowJavaScriptSpy).toBeCalledWith(origin, 'allow')
    })
  })

  describe('BLOCK_FINGERPRINTING', () => {
    let reloadTabSpy: jest.SpyInstance
    let setAllowFingerprintingSpy: jest.SpyInstance
    beforeEach(() => {
      reloadTabSpy = jest.spyOn(tabsAPI, 'reloadTab')
      setAllowFingerprintingSpy = jest.spyOn(shieldsAPI, 'setAllowFingerprinting')
    })
    afterEach(() => {
      reloadTabSpy.mockRestore()
      setAllowFingerprintingSpy.mockRestore()
    })
    it('should call setAllowFingerprinting', () => {
      expect(
        shieldsPanelReducer(state, {
          type: types.BLOCK_FINGERPRINTING,
          setting: 'allow'
        })).toEqual(state)
      expect(setAllowFingerprintingSpy).toBeCalledWith(origin, 'allow')
    })
  })

  describe('BLOCK_COOKIES', () => {
    let reloadTabSpy: jest.SpyInstance
    let setAllowCookiesSpy: jest.SpyInstance
    beforeEach(() => {
      reloadTabSpy = jest.spyOn(tabsAPI, 'reloadTab')
      setAllowCookiesSpy = jest.spyOn(shieldsAPI, 'setAllowCookies')
    })
    afterEach(() => {
      reloadTabSpy.mockRestore()
      setAllowCookiesSpy.mockRestore()
    })
    it('should call setAllowCookies', () => {
      expect(
        shieldsPanelReducer(state, {
          type: types.BLOCK_COOKIES,
          setting: 'allow'
        })).toEqual(state)
      expect(setAllowCookiesSpy).toBeCalledWith(origin, 'allow')
    })
  })

  describe('RESOURCE_BLOCKED', () => {
    let spy: jest.SpyInstance
    beforeEach(() => {
      spy = jest.spyOn(browserActionAPI, 'setBadgeText')
    })
    afterEach(() => {
      spy.mockRestore()
    })
    it('badge text update should include all resource types', () => {
      const stateWithBlockStats: State = {
        ...state,
        tabs: {
          2: {
            ...state.tabs[2],
            adsBlocked: 1,
            trackersBlocked: 2,
            httpsRedirected: 3,
            javascriptBlocked: 1,
            fingerprintingBlocked: 5
          }
        }
      }
      shieldsPanelReducer(stateWithBlockStats, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'javascript',
          tabId: 2,
          subresource: 'https://a.com/index.js'
        }
      })
      expect(spy).toBeCalledTimes(1)
      expect(spy.mock.calls[0][1]).toBe('12')
    })
    it('increments for JS blocking', () => {
      let nextState = shieldsPanelReducer(state, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'javascript',
          tabId: 2,
          subresource: 'https://test.hnq.vn/index.js'
        }
      })

      expect(nextState).toEqual({
        ...state,
        tabs: {
          ...state.tabs,
          2: {
            ...state.tabs[2],
            javascriptBlocked: 1,
            noScriptInfo: {
              'https://test.hnq.vn/index.js': { actuallyBlocked: true, willBlock: true, userInteracted: false }
            }
          }
        }
      })
    })
    it('increments JS blocking consecutively', () => {
      let nextState = shieldsPanelReducer(state, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'javascript',
          tabId: 2,
          subresource: 'https://a.com/index.js'
        }
      })
      expect(nextState).toEqual({
        ...state,
        tabs: {
          ...state.tabs,
          2: {
            ...state.tabs[2],
            javascriptBlocked: 1,
            noScriptInfo: {
              'https://a.com/index.js': { actuallyBlocked: true, willBlock: true, userInteracted: false }
            }
          }
        }
      })

      nextState = shieldsPanelReducer(nextState, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'javascript',
          tabId: 2,
          subresource: 'https://b.com/index.js'
        }
      })
      expect(nextState).toEqual({
        ...state,
        tabs: {
          ...state.tabs,
          2: {
            ...state.tabs[2],
            javascriptBlocked: 2,
            noScriptInfo: {
              'https://a.com/index.js': { actuallyBlocked: true, willBlock: true, userInteracted: false },
              'https://b.com/index.js': { actuallyBlocked: true, willBlock: true, userInteracted: false }
            }
          }
        }
      })
    })
    it('increments for fingerprinting blocked', () => {
      let nextState = shieldsPanelReducer(state, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'fingerprinting',
          tabId: 2,
          subresource: 'https://test.hnq.vn'
        }
      })
      expect(nextState).toEqual({
        ...state,
        tabs: {
          ...state.tabs,
          2: {
            ...state.tabs[2],
            fingerprintingBlocked: 1,
            fingerprintingBlockedResources: [ 'https://test.hnq.vn' ]
          }
        }
      })
    })
    it('increases same count consecutively', () => {
      let nextState = shieldsPanelReducer(state, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'ads',
          tabId: 2,
          subresource: 'https://test.hnq.vn'
        }
      })
      expect(nextState).toEqual({
        ...state,
        tabs: {
          ...state.tabs,
          2: {
            ...state.tabs[2],
            adsBlocked: 1,
            adsBlockedResources: [ 'https://test.hnq.vn' ]
          }
        }
      })

      nextState = shieldsPanelReducer(nextState, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'ads',
          tabId: 2,
          subresource: 'https://test2.hnq.vn'
        }
      })
      expect(nextState).toEqual({
        ...state,
        tabs: {
          ...state.tabs,
          2: {
            ...state.tabs[2],
            adsBlocked: 2,
            adsBlockedResources: [
              'https://test.hnq.vn',
              'https://test2.hnq.vn'
            ]
          }
        }
      })
    })
    it('increases same count consecutively without duplicates', () => {
      const tabId = 2
      let nextState = shieldsPanelReducer(state, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'ads',
          tabId: tabId,
          subresource: 'https://test.hnq.vn'
        }
      })
      expect(nextState.tabs[tabId].adsBlockedResources).toEqual(
        [ 'https://test.hnq.vn' ]
      )

      nextState = shieldsPanelReducer(nextState, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'ads',
          tabId: tabId,
          subresource: 'https://test2.hnq.vn'
        }
      })
      expect(nextState.tabs[tabId].adsBlockedResources).toEqual(
        [
          'https://test.hnq.vn',
          'https://test2.hnq.vn'
        ]
      )

      nextState = shieldsPanelReducer(nextState, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'ads',
          tabId: tabId,
          subresource: 'https://test2.hnq.vn'
        }
      })
      expect(nextState.tabs[tabId].adsBlockedResources).toEqual(
        [
          'https://test.hnq.vn',
          'https://test2.hnq.vn'
        ]
      )
    })
    it('increases different tab counts separately', () => {
      let nextState = deepFreeze(shieldsPanelReducer(state, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'ads',
          tabId: 2,
          subresource: 'https://test.hnq.vn'
        }
      }))
      expect(nextState).toEqual({
        ...state,
        tabs: {
          ...state.tabs,
          2: {
            ...state.tabs[2],
            adsBlocked: 1,
            adsBlockedResources: [
              'https://test.hnq.vn'
            ]
          }
        }
      })

      nextState = shieldsPanelReducer(nextState, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'ads',
          tabId: 3,
          subresource: 'https://test.hnq.vn'
        }
      })

      expect(nextState).toEqual({
        ...state,
        tabs: {
          ...state.tabs,
          2: {
            ...state.tabs[2],
            adsBlocked: 1,
            adsBlockedResources: [ 'https://test.hnq.vn' ]
          },
          3: {
            fingerprintingBlocked: 0,
            fingerprintingBlockedResources: [],
            httpsRedirected: 0,
            httpsRedirectedResources: [],
            javascriptBlocked: 0,
            noScriptInfo: {},
            trackersBlocked: 0,
            trackersBlockedResources: [],
            adsBlocked: 1,
            adsBlockedResources: [ 'https://test.hnq.vn' ]
          }
        }
      })
    })
    it('increases different resource types separately', () => {
      let nextState = deepFreeze(shieldsPanelReducer(state, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'ads',
          tabId: 2,
          subresource: 'https://test.hnq.vn'
        }
      }))
      expect(nextState).toEqual({
        ...state,
        tabs: {
          ...state.tabs,
          2: {
            ...state.tabs[2],
            adsBlocked: 1,
            adsBlockedResources: [ 'https://test.hnq.vn' ]
          }
        }
      })

      nextState = shieldsPanelReducer(nextState, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'trackers',
          tabId: 2,
          subresource: 'https://test.hnq.vn'
        }
      })

      expect(nextState).toEqual({
        ...state,
        tabs: {
          ...state.tabs,
          2: {
            ...state.tabs[2],
            adsBlocked: 1,
            trackersBlocked: 1,
            trackersBlockedResources: [ 'https://test.hnq.vn' ],
            adsBlockedResources: [ 'https://test.hnq.vn' ]
          }
        }
      })

      nextState = shieldsPanelReducer(nextState, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'httpUpgradableResources',
          tabId: 2,
          subresource: 'https://test.hnq.vn'
        }
      })
      expect(nextState).toEqual({
        ...state,
        tabs: {
          ...state.tabs,
          2: {
            ...state.tabs[2],
            adsBlocked: 1,
            trackersBlocked: 1,
            httpsRedirected: 1,
            trackersBlockedResources: [ 'https://test.hnq.vn' ],
            adsBlockedResources: [ 'https://test.hnq.vn' ],
            httpsRedirectedResources: [ 'https://test.hnq.vn' ]
          }
        }
      })
      nextState = shieldsPanelReducer(nextState, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'javascript',
          tabId: 2,
          subresource: 'https://test.hnq.vn/index.js'
        }
      })
      expect(nextState).toEqual({
        ...state,
        tabs: {
          ...state.tabs,
          2: {
            ...state.tabs[2],
            adsBlocked: 1,
            trackersBlocked: 1,
            httpsRedirected: 1,
            javascriptBlocked: 1,
            noScriptInfo: {
              'https://test.hnq.vn/index.js': { actuallyBlocked: true, willBlock: true, userInteracted: false }
            },
            trackersBlockedResources: [ 'https://test.hnq.vn' ],
            adsBlockedResources: [ 'https://test.hnq.vn' ],
            httpsRedirectedResources: [ 'https://test.hnq.vn' ]
          }
        }
      })
      nextState = shieldsPanelReducer(nextState, {
        type: types.RESOURCE_BLOCKED,
        details: {
          blockType: 'fingerprinting',
          tabId: 2,
          subresource: 'https://test.hnq.vn'
        }
      })
      expect(nextState).toEqual({
        ...state,
        tabs: {
          ...state.tabs,
          2: {
            ...state.tabs[2],
            adsBlocked: 1,
            trackersBlocked: 1,
            httpsRedirected: 1,
            javascriptBlocked: 1,
            fingerprintingBlocked: 1,
            noScriptInfo: {
              'https://test.hnq.vn/index.js': { actuallyBlocked: true, willBlock: true, userInteracted: false }
            },
            trackersBlockedResources: [ 'https://test.hnq.vn' ],
            adsBlockedResources: [ 'https://test.hnq.vn' ],
            fingerprintingBlockedResources: [ 'https://test.hnq.vn' ],
            httpsRedirectedResources: [ 'https://test.hnq.vn' ]
          }
        }
      })
    })
  })

  describe('BLOCK_ADS_TRACKERS', () => {
    let reloadTabSpy: jest.SpyInstance
    let setAllowAdsSpy: jest.SpyInstance
    let setAllowTrackersSpy: jest.SpyInstance
    beforeEach(() => {
      reloadTabSpy = jest.spyOn(tabsAPI, 'reloadTab')
      setAllowAdsSpy = jest.spyOn(shieldsAPI, 'setAllowAds')
      setAllowTrackersSpy = jest.spyOn(shieldsAPI, 'setAllowTrackers')
    })
    afterEach(() => {
      reloadTabSpy.mockRestore()
      setAllowAdsSpy.mockRestore()
      setAllowTrackersSpy.mockRestore()
    })
    it('should call setAllowAds and setAllowTrackers', () => {
      expect(
        shieldsPanelReducer(state, {
          type: types.BLOCK_ADS_TRACKERS,
          setting: 'block'
        })).toEqual(state)
      expect(setAllowAdsSpy).toBeCalledWith(origin, 'block')
      expect(setAllowTrackersSpy).toBeCalledWith(origin, 'block')
    })
  })

  describe('ALLOW_SCRIPT_ORIGINS_ONCE', () => {
    let reloadTabSpy: jest.SpyInstance
    let setAllowScriptOriginsOnceSpy: jest.SpyInstance
    beforeEach(() => {
      reloadTabSpy = jest.spyOn(tabsAPI, 'reloadTab')
      setAllowScriptOriginsOnceSpy = jest.spyOn(shieldsAPI, 'setAllowScriptOriginsOnce')
    })
    afterEach(() => {
      reloadTabSpy.mockRestore()
      setAllowScriptOriginsOnceSpy.mockRestore()
    })
    it('should call setAllowScriptOriginsOnce', () => {
      const tabId = 2
      expect(
        shieldsPanelReducer(state, {
          type: types.ALLOW_SCRIPT_ORIGINS_ONCE
        })).toEqual(state)
      expect(setAllowScriptOriginsOnceSpy).toBeCalledWith([], tabId)
    })
  })

  describe('SET_ADVANCED_VIEW_FIRST_ACCESS', () => {
    let updatePersistentDataSpy: jest.SpyInstance
    beforeEach(() => {
      updatePersistentDataSpy = jest.spyOn(shieldsPanelState, 'updatePersistentData')
    })
    afterEach(() => {
      updatePersistentDataSpy.mockRestore()
    })
    it('should call updatePersistentData', () => {
      const isFirstAccess: boolean = false
      const persistentData = { isFirstAccess }
      expect(
        shieldsPanelReducer(state, {
          type: types.SET_ADVANCED_VIEW_FIRST_ACCESS
        })).toEqual({ ...state, persistentData })
      expect(updatePersistentDataSpy).toBeCalledWith(state, persistentData)
    })
  })
})
