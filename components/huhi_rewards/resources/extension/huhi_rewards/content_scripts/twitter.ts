/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// Utils
import { getMessage } from '../background/api/locale_api'

interface TweetResponse {
  text: string,
  user: {
    name: string,
    screen_name: string,
    id_str: string
  },
  created_at: string
}

interface UserResponse {
  id_str: string
}

let timeout: any = null
let newTwitter = true

const getTwitterAPICredentials = () => {
  const msg = { type: 'getTwitterAPICredentials' }
  return new Promise(resolve => chrome.runtime.sendMessage(msg, resolve))
}

const getTweetDetails = async (tweetId: string) => {
  const credentialHeaders = await getTwitterAPICredentials()
  if (Object.keys(credentialHeaders).length === 0) {
    throw new Error(`Unable to make Twitter API request: no credential headers`)
  }

  const msg = {
    type: 'twitterGetTweetDetails',
    tweetId,
    credentialHeaders
  }
  return new Promise(resolve => chrome.runtime.sendMessage(msg, resolve))
}

const getUserDetails = async (screenName: string) => {
  const credentialHeaders = await getTwitterAPICredentials()
  if (Object.keys(credentialHeaders).length === 0) {
    throw new Error(`Unable to make Twitter API request: no credential headers`)
  }

  const msg = {
    type: 'twitterGetUserDetails',
    screenName,
    credentialHeaders
  }
  return new Promise(resolve => chrome.runtime.sendMessage(msg, resolve))
}

function getTweetId (tweet: Element) {
  if (!newTwitter) {
    return tweet.getAttribute('data-tweet-id')
  }
  const status = tweet.querySelector("a[href*='/status/']") as HTMLAnchorElement
  if (!status || !status.href) {
    return null
  }
  const tweetIdMatches = status.href.match(/status\/(\d+)/)
  if (!tweetIdMatches || tweetIdMatches.length < 2) {
    return null
  }
  return tweetIdMatches[1]
}

const getTweetMetaData = (tweet: Element, tweetId: string): Promise<RewardsTip.MediaMetaData> => {
  if (!tweet) {
    return Promise.reject(null)
  }

  return getTweetDetails(tweetId)
    .then((tweetDetails: TweetResponse) => {
      const mediaMetadata: RewardsTip.MediaMetaData = {
        mediaType: 'twitter',
        twitterName: tweetDetails.user.name,
        screenName: tweetDetails.user.screen_name,
        userId: tweetDetails.user.id_str,
        tweetId,
        tweetTimestamp: Date.parse(tweetDetails.created_at) / 1000,
        tweetText: tweetDetails.text
      }
      return mediaMetadata
    })
    .catch(error => {
      console.error(`Failed to fetch tweet details for ${tweetId}: ${error.message}`)
      return Promise.reject(error)
    })
}

const getTweetMetaDataForOldTwitter = (tweet: Element, tweetId: string): RewardsTip.MediaMetaData | null => {
  if (!tweet) {
    return null
  }

  const tweetTextElements = tweet.getElementsByClassName('tweet-text')
  if (!tweetTextElements || tweetTextElements.length === 0) {
    return null
  }

  const tweetText = tweetTextElements[0] as HTMLElement

  const tweetTimestampElements = tweet.getElementsByClassName('js-short-timestamp')
  if (!tweetTimestampElements || tweetTimestampElements.length === 0) {
    return null
  }

  const tweetTimestamp = tweetTimestampElements[0].getAttribute('data-time') || ''

  return {
    mediaType: 'twitter',
    twitterName: tweet.getAttribute('data-name') || '',
    screenName: tweet.getAttribute('data-screen-name') || '',
    userId: tweet.getAttribute('data-user-id') || '',
    tweetId,
    tweetTimestamp: parseInt(tweetTimestamp, 10) || 0,
    tweetText: tweetText.innerText || ''
  }
}

const tipTwitterUser = (mediaMetaData: RewardsTip.MediaMetaData) => {
  const msg = { type: 'tipInlineMedia', mediaMetaData }
  chrome.runtime.sendMessage(msg)
}

const onTipActionKey = (e: KeyboardEvent) => {
  if (e.key !== 'Enter' && e.code !== 'Space') {
    return
  }

  const activeItem = e.target as HTMLElement
  if (!activeItem) {
    return
  }

  const shadowRoot = activeItem.shadowRoot
  if (!shadowRoot) {
    return
  }

  const tipButton: HTMLElement | null = shadowRoot.querySelector('.js-actionButton')
  if (tipButton) {
    tipButton.click()
  }
}

const createHuhiTipAction = (tweet: Element, tweetId: string, numActions: number) => {
  // Create the tip action
  const hasUserActions = numActions > 3
  const huhiTipAction = document.createElement('div')
  huhiTipAction.className = 'ProfileTweet-action js-tooltip action-huhi-tip'
  huhiTipAction.style.display = 'inline-block'
  huhiTipAction.style.minWidth = '80px'
  huhiTipAction.style.textAlign = hasUserActions ? 'right' : 'start'
  huhiTipAction.setAttribute('role', 'button')
  huhiTipAction.setAttribute('tabindex', '0')
  huhiTipAction.setAttribute('data-original-title', getMessage('twitterTipsHoverText'))
  huhiTipAction.addEventListener('keydown', onTipActionKey)

  // Create the tip button
  const huhiTipButton = document.createElement('button')
  huhiTipButton.className = 'ProfileTweet-actionButton u-textUserColorHover js-actionButton'
  huhiTipButton.style.background = 'transparent'
  huhiTipButton.style.border = '0'
  huhiTipButton.style.color = '#657786'
  huhiTipButton.style.cursor = 'pointer'
  huhiTipButton.style.display = 'inline-block'
  huhiTipButton.style.fontSize = '16px'
  huhiTipButton.style.lineHeight = '1'
  huhiTipButton.style.outline = '0'
  huhiTipButton.style.padding = '0 2px'
  huhiTipButton.style.position = 'relative'
  huhiTipButton.type = 'button'
  huhiTipButton.onclick = function (event) {
    if (newTwitter) {
      getTweetMetaData(tweet, tweetId)
        .then(tweetMetaData => {
          if (tweetMetaData) {
            tipTwitterUser(tweetMetaData)
          }
        })
        .catch(error => {
          console.error(`Failed to fetch tweet metadata for ${tweet}:`, error)
        })
    } else {
      const tweetMetaData = getTweetMetaDataForOldTwitter(tweet, tweetId)
      if (tweetMetaData) {
        tipTwitterUser(tweetMetaData)
      }
    }
    event.stopPropagation()
  }

  if (newTwitter && tweet && tweet.getAttribute('data-testid') === 'tweetDetail') {
    huhiTipButton.style.marginTop = '12px'
  }

  // Create the tip icon container
  const huhiTipIconContainer = document.createElement('div')
  huhiTipIconContainer.className = 'IconContainer js-tooltip'
  huhiTipIconContainer.style.display = 'inline-block'
  huhiTipIconContainer.style.lineHeight = '0'
  huhiTipIconContainer.style.position = 'relative'
  huhiTipIconContainer.style.verticalAlign = 'middle'
  huhiTipButton.appendChild(huhiTipIconContainer)

  // Create the tip icon
  const huhiTipIcon = document.createElement('span')
  huhiTipIcon.className = 'Icon Icon--medium'
  huhiTipIcon.style.background = 'transparent'
  huhiTipIcon.style.content = 'url(\'data:image/svg+xml;utf8,<svg version="1.1" id="Layer_1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px" viewBox="0 0 105 100" style="enable-background:new 0 0 105 100;" xml:space="preserve"><style type="text/css">.st1{fill:%23662D91;}.st2{fill:%239E1F63;}.st3{fill:%23FF5000;}.st4{fill:%23FFFFFF;stroke:%23FF5000;stroke-width:0.83;stroke-miterlimit:10;}</style><title>BAT_icon</title><g id="Layer_2_1_"><g id="Layer_1-2"><polygon class="st1" points="94.8,82.6 47.4,55.4 0,82.9 "/><polygon class="st2" points="47.4,0 47.1,55.4 94.8,82.6 "/><polygon class="st3" points="0,82.9 47.2,55.9 47.4,0 "/><polygon class="st4" points="47.1,33.7 28,66.5 66.7,66.5 "/></g></g></svg>\')'
  huhiTipIcon.style.display = 'inline-block'
  huhiTipIcon.style.fontSize = '18px'
  huhiTipIcon.style.fontStyle = 'normal'
  huhiTipIcon.style.height = '16px'
  huhiTipIcon.style.marginTop = '5px'
  huhiTipIcon.style.position = 'relative'
  huhiTipIcon.style.verticalAlign = 'baseline'
  huhiTipIcon.style.width = '16px'
  huhiTipIconContainer.appendChild(huhiTipIcon)

  // Create the tip action count (typically used to present a counter
  // associated with the action, but we'll use it to display a static
  // action label)
  const huhiTipActionCount = document.createElement('span')
  huhiTipActionCount.className = 'ProfileTweet-actionCount'
  huhiTipActionCount.style.color = '#657786'
  huhiTipActionCount.style.display = 'inline-block'
  huhiTipActionCount.style.fontSize = '12px'
  huhiTipActionCount.style.fontWeight = 'bold'
  huhiTipActionCount.style.lineHeight = '1'
  huhiTipActionCount.style.marginLeft = '6px'
  huhiTipActionCount.style.position = 'relative'
  huhiTipActionCount.style.verticalAlign = 'text-bottom'
  huhiTipButton.appendChild(huhiTipActionCount)

  // Create the tip action count presentation
  const huhiTipActionCountPresentation = document.createElement('span')
  huhiTipActionCountPresentation.className = 'ProfileTweet-actionCountForPresentation'
  huhiTipActionCountPresentation.textContent = getMessage('twitterTipsIconLabel')
  huhiTipActionCount.appendChild(huhiTipActionCountPresentation)

  // Create the shadow DOM root that hosts our injected DOM elements
  const shadowRoot = huhiTipAction.attachShadow({ mode: 'open' })
  shadowRoot.appendChild(huhiTipButton)

  // Create style element for hover color
  const style = document.createElement('style')
  style.innerHTML = '.ProfileTweet-actionButton :hover { color: #FB542B }'
  shadowRoot.appendChild(style)

  return huhiTipAction
}

const configureHuhiTipAction = () => {
  clearTimeout(timeout)
  chrome.runtime.sendMessage('rewardsEnabled', function (rewards) {
    const msg = {
      type: 'inlineTippingPlatformEnabled',
      key: 'twitter'
    }
    chrome.runtime.sendMessage(msg, function (inlineTip) {
      const tippingEnabled = rewards.enabled && inlineTip.enabled
      let tweets = document.querySelectorAll('[data-testid="tweet"], [data-testid="tweetDetail"]')
      // Reset page state since first run of this function may have been pre-content
      newTwitter = true
      if (tweets.length === 0) {
        tweets = document.querySelectorAll('.tweet')
        newTwitter = false
      }
      for (let i = 0; i < tweets.length; ++i) {
        let actions
        const tweetId = getTweetId(tweets[i])
        if (!tweetId) {
          continue
        }
        if (newTwitter) {
          actions = tweets[i].querySelector('[role="group"]')
        } else {
          actions = tweets[i].querySelector('.js-actions')
        }
        if (!actions) {
          continue
        }
        const numActions = actions.querySelectorAll(':scope > div').length || 0
        const huhiTipActions = actions.getElementsByClassName('action-huhi-tip')
        if (tippingEnabled && huhiTipActions.length === 0) {
          actions.appendChild(createHuhiTipAction(tweets[i], tweetId, numActions))
        } else if (!tippingEnabled && huhiTipActions.length === 1) {
          actions.removeChild(huhiTipActions[0])
        }
      }
    })
  })
  timeout = setTimeout(configureHuhiTipAction, 3000)
}

// In order to deal with infinite scrolling and overlays, periodically
// check if injection needs to occur (mitigate the performance cost
// by only running this when the foreground tab is active or visible)
document.addEventListener('visibilitychange', function () {
  clearTimeout(timeout)
  if (!document.hidden) {
    timeout = setTimeout(configureHuhiTipAction, 3000)
  }
})

// Call the Twitter API to retrieve the user ID and then pass it
// to our backend using an alternate profile page URL. This allows us
// to pass the user ID to our backend without the need to make additional
// API changes to accomodate a user ID.
chrome.runtime.onMessage.addListener((msg, sender, sendResponse) => {
  const action = typeof msg === 'string' ? msg : msg.type
  switch (action) {
    case 'getProfileUrl': {
      const screenName = msg.screenName
      getUserDetails(screenName)
        .then((userDetails: UserResponse) => {
          const userId = userDetails.id_str
          const profileUrl = `https://twitter.com/intent/user?user_id=${userId}&screen_name=${screenName}`
          sendResponse({ profileUrl })
        }).catch(error => {
          console.error(`Failed to fetch user details for ${screenName}: ${error.message}`)
          return Promise.reject(error)
        })
      // Must return true for asynchronous calls to sendResponse
      return true
    }
    default:
      return false
  }
})

configureHuhiTipAction()
