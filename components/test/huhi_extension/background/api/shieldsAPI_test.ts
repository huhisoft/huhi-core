/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import actions from '../../../../huhi_extension/extension/huhi_extension/background/actions/shieldsPanelActions'
import * as shieldsAPI from '../../../../huhi_extension/extension/huhi_extension/background/api/shieldsAPI'
import { activeTabData } from '../../../testData'
import { ShieldDetails } from '../../../../huhi_extension/extension/huhi_extension/types/actions/shieldsPanelActions'

describe('Shields API', () => {
  describe('getShieldSettingsForTabData', () => {
    it('returns a rejected promise when no tab data is specified', (cb) => {
      shieldsAPI.getShieldSettingsForTabData(undefined)
        .catch(() => {
          cb()
        })
    })

    it('resolves the returned promise with shield settings for the tab data', (cb) => {
      const tab: chrome.tabs.Tab = {
        url: 'https://www.huhisoft.com/serg/dont/know/pokemon',
        id: 5,
        index: 1,
        pinned: false,
        highlighted: false,
        windowId: 1,
        active: true,
        incognito: false,
        selected: false,
        discarded: false,
        autoDiscardable: false
      }

      expect.assertions(1)
      shieldsAPI.getShieldSettingsForTabData(tab).then((data) => {
        expect(data).toEqual({
          url: 'https://www.huhisoft.com/serg/dont/know/pokemon',
          origin: 'https://www.huhisoft.com',
          hostname: 'www.huhisoft.com',
          huhiShields: 'block',
          ads: 'block',
          trackers: 'block',
          cosmeticFiltering: true,
          firstPartyCosmeticFiltering: false,
          httpUpgradableResources: 'block',
          javascript: 'block',
          fingerprinting: 'block',
          id: 5,
          cookies: 'block'
        })
        cb()
      })
      .catch((e: Error) => {
        console.error(e.toString())
      })
    })
  })

  describe('getTabData', () => {
    let spy: jest.SpyInstance
    const tabId = 2
    beforeAll(() => {
      spy = jest.spyOn(chrome.tabs, 'getAsync')
    })
    afterEach(() => {
      spy.mockRestore()
    })

    it('calls chrome.tabs.getAsync for the active tab', () => {
      expect.assertions(1)
      shieldsAPI.getTabData(tabId)
      expect(spy).toBeCalledWith(tabId)
    })

    it('resolves the promise with an array', (cb) => {
      expect.assertions(1)
      shieldsAPI.getTabData(tabId)
      .then((tab: chrome.tabs.Tab) => {
        expect(tab).toEqual(activeTabData)
        cb()
      })
      .catch((e: Error) => {
        console.error(e.toString())
      })
    })
  })

  describe('requestShieldPanelData', () => {
    let spy: jest.SpyInstance
    const tabId = 2
    beforeEach(() => {
      spy = jest.spyOn(actions, 'shieldsPanelDataUpdated')
    })
    afterEach(() => {
      spy.mockRestore()
    })
    it('resolves and calls requestShieldPanelData', (cb) => {
      const details: ShieldDetails = {
        ads: 'block',
        trackers: 'block',
        cosmeticFiltering: true,
        firstPartyCosmeticFiltering: false,
        httpUpgradableResources: 'block',
        origin: 'https://www.huhisoft.com',
        hostname: 'www.huhisoft.com',
        id: 2,
        javascript: 'block',
        fingerprinting: 'block',
        cookies: 'block'
      }

      expect.assertions(2)
      shieldsAPI.requestShieldPanelData(tabId)
        .then(() => {
          expect(spy).toBeCalledTimes(1)
          expect(spy.mock.calls[0][0]).toEqual({
            ...details,
            url: 'https://www.huhisoft.com/test',
            huhiShields: 'block'
          })
          cb()
        })
        .catch((e: Error) => {
          console.error(e.toString())
        })
    })
  })

  describe('setAllowAds', () => {
    let spy: jest.SpyInstance
    beforeEach(() => {
      spy = jest.spyOn(chrome.huhiShields, 'setAdControlTypeAsync')
    })
    afterEach(() => {
      spy.mockRestore()
    })
    it('calls chrome.huhiShields.setAdControlTypeAsync with the correct args', () => {
      shieldsAPI.setAllowAds('https://www.huhisoft.com', 'block')
        .catch(() => {
          expect(true).toBe(false)
        })
      const arg0 = spy.mock.calls[0][0]
      const arg1 = spy.mock.calls[0][1]
      expect.assertions(2)
      expect(arg0).toEqual('block')
      expect(arg1).toEqual('https://www.huhisoft.com')
    })
  })

  describe('setAllowHTTPUpgradableResource', () => {
    let spy: jest.SpyInstance
    beforeEach(() => {
      spy = jest.spyOn(chrome.huhiShields, 'setHTTPSEverywhereEnabledAsync')
    })
    afterEach(() => {
      spy.mockRestore()
    })
    it('calls chrome.huhiShields.setHTTPSEverywhereEnabledAsync with the correct args', () => {
      shieldsAPI.setAllowHTTPUpgradableResources('https://www.huhisoft.com', 'block')
        .catch(() => {
          expect(true).toBe(false)
        })
      const arg0 = spy.mock.calls[0][0]
      const arg1 = spy.mock.calls[0][1]
      expect.assertions(2)
      expect(arg0).toEqual(true)
      expect(arg1).toEqual('https://www.huhisoft.com')
    })
  })

  describe('setAllowJavaScript', () => {
    let spy: jest.SpyInstance
    beforeEach(() => {
      spy = jest.spyOn(chrome.huhiShields, 'setNoScriptControlTypeAsync')
    })
    afterEach(() => {
      spy.mockRestore()
    })
    it('calls chrome.huhiShields.setNoScriptControlTypeAsync with the correct args', () => {
      shieldsAPI.setAllowJavaScript('https://www.huhisoft.com', 'block')
        .catch(() => {
          expect(true).toBe(false)
        })
      const arg0 = spy.mock.calls[0][0]
      const arg1 = spy.mock.calls[0][1]
      expect.assertions(2)
      expect(arg0).toEqual('block')
      expect(arg1).toEqual('https://www.huhisoft.com')
    })
  })

  describe('setAllowFingerprinting', () => {
    let spy: jest.SpyInstance
    beforeEach(() => {
      spy = jest.spyOn(chrome.huhiShields, 'setFingerprintingControlTypeAsync')
    })
    afterEach(() => {
      spy.mockRestore()
    })
    it('calls chrome.huhiShields.setFingerprintingControlTypeAsync with the correct args', () => {
      shieldsAPI.setAllowFingerprinting('https://www.huhisoft.com', 'block')
        .catch(() => {
          expect(true).toBe(false)
        })
      const arg0 = spy.mock.calls[0][0]
      const arg1 = spy.mock.calls[0][1]
      expect.assertions(2)
      expect(arg0).toEqual('block')
      expect(arg1).toEqual('https://www.huhisoft.com')
    })
  })

  describe('setAllowCookies', () => {
    let spy: jest.SpyInstance
    beforeEach(() => {
      spy = jest.spyOn(chrome.huhiShields, 'setCookieControlTypeAsync')
    })
    afterEach(() => {
      spy.mockRestore()
    })
    it('calls chrome.huhiShields.setCookieControlTypeAsync with the correct args', () => {
      shieldsAPI.setAllowCookies('https://www.huhisoft.com', 'block')
        .catch(() => {
          expect(true).toBe(false)
        })
      const arg0 = spy.mock.calls[0][0]
      const arg1 = spy.mock.calls[0][1]
      expect.assertions(2)
      expect(arg0).toEqual('block')
      expect(arg1).toEqual('https://www.huhisoft.com')
    })
  })

  describe('toggleShieldsValue', () => {
    it('toggles \'allow\' to \'block\'', () => {
      expect(shieldsAPI.toggleShieldsValue('allow')).toBe('block')
    })
    it('toggles \'block\' to \'allow\'', () => {
      expect(shieldsAPI.toggleShieldsValue('block')).toBe('allow')
    })
  })

  describe('setAllowScriptOriginsOnce', () => {
    let spy: jest.SpyInstance
    beforeEach(() => {
      spy = jest.spyOn(chrome.huhiShields, 'allowScriptsOnce')
    })
    afterEach(() => {
      spy.mockRestore()
    })
    it('calls chrome.huhiShields.allowScriptsOnce with the correct args', () => {
      shieldsAPI.setAllowScriptOriginsOnce(['https://a.com/', 'https://b.com/'], 2)
        .catch(() => {
          expect(true).toBe(false)
        })
      const arg0 = spy.mock.calls[0][0]
      expect.assertions(2)
      expect(arg0).toEqual(['https://a.com/', 'https://b.com/'])
      const arg1 = spy.mock.calls[0][1]
      expect(arg1).toBe(2)
    })
    it('passes 3 args to chrome.huhiShields.allowScriptsOnce', () => {
      shieldsAPI.setAllowScriptOriginsOnce(['https://a.com/', 'https://b.com/'], 2)
        .catch(() => {
          expect(true).toBe(false)
        })
      expect.assertions(1)
      expect(spy.mock.calls[0].length).toBe(3) // include callback
    })
    it('resolves the returned promise', (cb) => {
      shieldsAPI.setAllowScriptOriginsOnce(['https://a.com/', 'https://b.com/'], 2)
      .then(() => {
        cb()
      })
      .catch((e: Error) => {
        console.error(e.toString())
      })
    })
  })
})
