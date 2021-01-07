/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// Initial state
import { defaultState as welcomeData } from '../../components/huhi_welcome_ui/storage'
import { defaultState as rewardsData } from '../../components/huhi_rewards/resources/page/storage'
import { defaultState as adblockData } from '../../components/huhi_adblock_ui/storage'

// Types
import { Tab } from '../huhi_extension/extension/huhi_extension/types/state/shieldsPannelState'
import { BlockDetails } from '../huhi_extension/extension/huhi_extension/types/actions/shieldsPanelActions'

// Helpers
import * as deepFreeze from 'deep-freeze-node'

export class ChromeEvent {
  listeners: Array<() => void>

  constructor () {
    this.listeners = []
  }

  emit (...args: Array<() => void>) {
    this.listeners.forEach((cb: () => void) => cb.apply(null, args))
  }

  addListener (cb: () => void) {
    this.listeners.push(cb)
  }
}

export const welcomeInitialState: Welcome.ApplicationState = { welcomeData }

export const rewardsInitialState: Rewards.ApplicationState = { rewardsData }

export const adblockInitialState: AdBlock.ApplicationState = { adblockData }

export const newTabInitialState: NewTab.ApplicationState = {
  newTabData: {
    showBackgroundImage: false,
    showSettingsMenu: false,
    topSites: [],
    excludedSites: [],
    gridSites: [],
    showEmptyPage: false,
    isIncognito: new ChromeEvent(),
    useAlternativePrivateSearchEngine: false,
    torCircuitEstablished: false,
    torInitProgress: '',
    isTor: false,
    isQwant: false,
    stats: {
      adsBlockedStat: 0,
      javascriptBlockedStat: 0,
      bandwidthSavedStat: 0,
      fingerprintingBlockedStat: 0
    }
  }
}

interface CustomTab extends Tab {
  url: string
}

interface Tabs {
  [key: number]: CustomTab
}

export const tabs: Tabs = {
  2: {
    id: 2,
    url: 'https://www.hnq.vn/test',
    origin: 'https://www.hnq.vn',
    hostname: 'www.hnq.vn',
    ads: 'block',
    adsBlocked: 0,
    trackers: 'block',
    httpUpgradableResources: 'block',
    javascript: 'block',
    fingerprinting: 'block',
    cookies: 'block',
    controlsOpen: false,
    httpsRedirected: 0,
    javascriptBlocked: 0,
    fingerprintingBlocked: 0,
    huhiShields: 'block',
    trackersBlocked: 0,
    noScriptInfo: {},
    adsBlockedResources: [],
    trackersBlockedResources: [],
    httpsRedirectedResources: [],
    fingerprintingBlockedResources: []
  }
}

export const activeTabData = tabs[2]

export const blockedResource: BlockDetails = {
  blockType: 'ads',
  tabId: 2,
  subresource: 'https://www.hnq.vn/test'
}

// see: https://developer.chrome.com/extensions/events
interface OnMessageEvent extends chrome.events.Event<(message: object, options: any, responseCallback: any) => void> {
  emit: (message: object) => void
}

type MockSettingsStore = {
  [key: string]: chrome.settingsPrivate.PrefObject
}

// Initialize with defaults.
// TODO: do this in individual tests that rely on individual settings,
//   using the `addMockSetting` function
let mockSettings: MockSettingsStore = {
  ['huhi.shields.advanced_view_enabled']: {
    key: 'huhi.shields.advanced_view_enabled',
    type: 'BOOLEAN',
    value: false
  },
  ['huhi.shields.stats_badge_visible']: {
    key: 'huhi.shields.stats_badge_visible',
    type: 'BOOLEAN',
    value: true
  }
}

export function addMockSetting (key: string, pref: chrome.settingsPrivate.PrefObject) {
  mockSettings[key] = pref
}

export function clearMockSettings () {
  mockSettings = {}
}

export const getMockChrome = () => {
  let mock = {
    send: (methodName: string, ...args: Array<any>) => undefined,
    getVariableValue: () => undefined,
    huhiRewards: {
      getPublisherData: (id: number, url: string, favicon: string) => undefined
    },
    huhiTheme: {
      setHuhiThemeType: function (theme: string) {
        return
      }
    },
    runtime: {
      onMessage: new ChromeEvent(),
      onConnect: new ChromeEvent(),
      onStartup: new ChromeEvent(),
      onMessageExternal: new ChromeEvent(),
      onConnectExternal: new ChromeEvent(),
      // see: https://developer.chrome.com/apps/runtime#method-sendMessage
      sendMessage: function (message: object, responseCallback: () => void) {
        const onMessage = chrome.runtime.onMessage as OnMessageEvent
        onMessage.emit(message)
        responseCallback()
      }
    },
    browserAction: {
      setBadgeBackgroundColor: function (properties: object) {
        return
      },
      setBadgeText: function (textProperties: object) {
        return
      },
      setIcon: function (iconProperties: object) {
        return
      },
      enable: function (tabId?: number) {
        return
      },
      disable: function (tabId?: number) {
        return
      }
    },
    tabs: {
      queryAsync: function () {
        return Promise.resolve([activeTabData])
      },
      getAsync: function (tabId: number) {
        return Promise.resolve(tabs[tabId])
      },
      create: function (createProperties: object, cb: () => void) {
        setImmediate(cb)
      },
      reload: function (tabId: number, reloadProperties: object, cb: () => void) {
        setImmediate(cb)
      },
      insertCSS: function (details: jest.SpyInstance) {
        return
      },
      query: function (queryInfo: chrome.tabs.QueryInfo, callback: (result: chrome.tabs.Tab[]) => void) {
        return callback
      },
      sendMessage: function (tabID: Number, message: any, options: object, responseCallback: any) {
        return responseCallback
      },
      onActivated: new ChromeEvent(),
      onCreated: new ChromeEvent(),
      onUpdated: new ChromeEvent()
    },
    windows: {
      onFocusChanged: new ChromeEvent(),
      onCreated: new ChromeEvent(),
      onRemoved: new ChromeEvent(),
      getAllAsync: function () {
        return new Promise(() => [])
      }
    },
    huhiShields: {
      onBlocked: new ChromeEvent(),
      allowScriptsOnce: function (origins: Array<string>, tabId: number, cb: () => void) {
        setImmediate(cb)
      },
      getHuhiShieldsEnabledAsync: function (url: string) {
        return Promise.resolve(false)
      },
      shouldDoCosmeticFilteringAsync: function (url: string) {
        return Promise.resolve(true)
      },
      getAdControlTypeAsync: function (url: string) {
        return Promise.resolve('block')
      },
      isFirstPartyCosmeticFilteringEnabledAsync: function (url: string) {
        return Promise.resolve(false)
      },
      getCookieControlTypeAsync: function (url: string) {
        return Promise.resolve('block')
      },
      getFingerprintingControlTypeAsync: function (url: string) {
        return Promise.resolve('block')
      },
      getHTTPSEverywhereEnabledAsync: function (url: string) {
        return Promise.resolve(true)
      },
      getNoScriptControlTypeAsync: function (url: string) {
        return Promise.resolve('block')
      },
      setHuhiShieldsEnabledAsync: function (url: string, enabled: boolean) {
        return new Promise(() => [])
      },
      setAdControlTypeAsync: function (url: string, controlType: string) {
        return new Promise(() => [])
      },
      setCosmeticFilteringControlTypeAsync: function (url: string, controlType: string) {
        return new Promise(() => [])
      },
      setCookieControlTypeAsync: function (url: string, controlType: string) {
        return new Promise(() => [])
      },
      setFingerprintingControlTypeAsync: function (url: string, controlType: string) {
        return new Promise(() => [])
      },
      setHTTPSEverywhereEnabledAsync: function (url: string, enabled: boolean) {
        return new Promise(() => [])
      },
      setNoScriptControlTypeAsync: function (url: string, controlType: string) {
        return new Promise(() => [])
      }
    },
    i18n: {
      getMessage: function (message: string) {
        return
      }
    },
    storage: {
      local: {
        get: function (callback: (items: { [key: string]: any }) => void): void {
          return
        },
        set: function (items: Object, callback?: () => void): void {
          return
        }
      }
    },
    extension: {
      inIncognitoContext: new ChromeEvent()
    },
    topSites: {
      get: function (cb) {
        cb([])
      }
    },
    bookmarks: {
      create: function (bookmark: chrome.bookmarks.BookmarkCreateArg, callback?: (result: chrome.bookmarks.BookmarkTreeNode[]) => void) {
        return
      },
      remove: function (id: string, callback?: Function) {
        return
      },
      search: function (query: string, callback: (results: chrome.bookmarks.BookmarkTreeNode[]) => void) {
        return
      }
    },
    contextMenus: {
      create: function (data: any) {
        return Promise.resolve()
      },
      onBlocked: new ChromeEvent(),
      allowScriptsOnce: function (origins: Array<string>, tabId: number, cb: () => void) {
        setImmediate(cb)
      },
      onClicked: new ChromeEvent()
    },
    settingsPrivate: {
      getPref (key: string, callback: chrome.settingsPrivate.GetPrefCallback): void {
        if (!mockSettings[key]) {
          throw new Error(`Mock Settings Store did not have a value for key "${key}". Please seed the store before the test is run using \`addMockSetting\``)
        }
        callback(mockSettings[key])
      },
      setPref (key: string, value: any, pageId?: string | null, callback?: chrome.settingsPrivate.SetPrefCallback): void {
        if (!mockSettings[key]) {
          throw new Error(`Mock Settings Store did not have a value for key "${key}". Please seed the store before the test is run using \`addMockSetting\`.`)
        }
        mockSettings[key].value = value
        callback(true)
      },
      PrefType: {
        BOOLEAN: 'BOOLEAN',
        NUMBER: 'NUMBER',
        STRING: 'STRING',
        URL: 'URL',
        LIST: 'LIST',
        DICTIONARY: 'DICTIONARY'
      }
    }
  }
  return mock
}

export const window = () => {
  let mock = {
    prompt: function (text: String) {
      return text
    }
  }
  return mock
}

export const initialState = deepFreeze({
  dappDetection: {},
  runtime: {},
  shieldsPanel: {
    currentWindowId: -1,
    tabs: {},
    windows: {},
    persistentData: { isFirstAccess: true },
    settingsData: { showAdvancedView: false, statsBadgeVisible: true }
  }
})

export const mockThemes = [
  {
    name: 'Dark',
    index: '0'
  },
  {
    name: 'Light',
    index: '1'
  }
]

export const mockSearchProviders = [
  {
    canBeDefault: true,
    canBeEdited: true,
    canBeRemoved: true,
    default: true,
    displayName: 'DuckDuckGo',
    iconURL: 'https://duckduckgo.com/favicon.ico',
    id: 3,
    isOmniboxExtension: false,
    keyword: ':d',
    modelIndex: 1,
    name: 'DuckDuckGo',
    url: 'https://duckduckgo.com/?q=%s&t=huhi',
    urlLocked: true
  }
]

export const mockImportSources = [
  {
    autofillFormData : false,
    cookies : true,
    favorites : true,
    history : true,
    index : 1,
    ledger : false,
    name :  `Chrome Person 1`,
    passwords : true,
    search : false,
    stats : false,
    windows : false
  },
  {
    autofillFormData : false,
    cookies : true,
    favorites : true,
    history : true,
    index : 0,
    ledger : false,
    name :  `Safari`,
    passwords : true,
    search : false,
    stats : false,
    windows : false
  },
  {
    autofillFormData : false,
    cookies : true,
    favorites : true,
    history : true,
    index : 2,
    ledger : false,
    name :  `Bookmarks HTML File`,
    passwords : true,
    search : false,
    stats : false,
    windows : false
  }
]
