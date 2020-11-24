/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// Utils
import { getMessage } from '../background/api/locale_api'

let timeout: any = null

const isOldReddit = () => {
  const redditUrl = new URL(document.URL)
  return redditUrl.hostname.startsWith('old') ||
    redditUrl.hostname.startsWith('np')
}

const getOldRedditMetaData = (redditPost: Element): RewardsTip.MediaMetaData | null => {
  if (!redditPost) {
    return null
  }
  let postText = ''
  let postTextElements = redditPost.getElementsByClassName('md')
  let postTitleElement: HTMLAnchorElement | null = redditPost.querySelector('a[data-event-action="title"]')
  if (!postTextElements || postTextElements.length === 0) {
    postText = postTitleElement && postTitleElement.innerText ? postTitleElement.innerText : ''
  } else {
    const divPostTextElement = (postTextElements[0] as HTMLDivElement)
    if (divPostTextElement && divPostTextElement.innerText) {
      postText = divPostTextElement.innerText
    }
  }
  if (postText.length > 200) {
    postText = postText.substr(0, 200) + '...'
  }

  let userName = ''
  // it's possible that two author classes could show up on a comments feed.
  // The post author and an author commenting
  // Get 'entry' div first to id the author commenting
  let authorAnchorElement
  let entryDiv = redditPost.getElementsByClassName('entry')
  if (entryDiv) {
    authorAnchorElement = entryDiv[0].getElementsByClassName('author')
  }
  if (authorAnchorElement) {
    const divPostTextElement = (authorAnchorElement[0] as HTMLAnchorElement)
    if (divPostTextElement && divPostTextElement.textContent) {
      userName = divPostTextElement.textContent
    }
  }

  let postRelDate = ''
  let postDateElement = redditPost.getElementsByTagName('time')
  if (postDateElement && postDateElement.length > 0) {
    postRelDate = postDateElement[0].textContent || ''
  }

  return {
    mediaType: 'reddit',
    userName: userName,
    postText: postText || '',
    postRelDate: postRelDate || ''
  }
}

const getRedditMetaData = (redditPost: Element): RewardsTip.MediaMetaData | null => {
  if (!redditPost) {
    return null
  }

  let postText = ''
  let postTextElements = redditPost.getElementsByTagName('p')
  if (!postTextElements || postTextElements.length === 0) {
    postTextElements = redditPost.getElementsByTagName('h3')
    if (postTextElements && postTextElements.length > 0) {
      if (postTextElements[0].innerText) {
        postText = postTextElements[0].innerText
      }
    } else {
      postTextElements = redditPost.getElementsByTagName('h1')
      if (postTextElements[0].innerText) {
        postText = postTextElements[0].innerText
      }
    }
  } else {
    let postTextElement = (postTextElements[0] as HTMLElement).parentElement
    if (postTextElement && postTextElement.innerText) {
      postText = postTextElement.innerText
    }
  }
  if (postText.length > 200) {
    postText = postText.substr(0, 200) + '...'
  }

  const anchor: HTMLAnchorElement | null = redditPost.querySelector('a[href^="/user/"]:not([data-click-id="body"]):not([data-click-id="subreddit"])')
  let userName = ''
  if (anchor && anchor.textContent) {
    userName = anchor.textContent.startsWith('u/') ? anchor.textContent.split('/')[1] : anchor.textContent
  }

  let postRelDate = ''
  let postDateElement = redditPost.querySelector('a[data-click-id="timestamp"]')
  if (postDateElement) {
    postRelDate = postDateElement.textContent || ''
  } else {
    const commentPartElement = redditPost.querySelector('div[data-test-id="comment"]')
    if (commentPartElement) {
      const authorRowDiv = commentPartElement.previousElementSibling
      if (authorRowDiv) {
        const timeLink = authorRowDiv.getElementsByTagName('a')
        if (timeLink && timeLink.length > 1) {
          const timeSpan = timeLink[1].getElementsByTagName('span')
          if (timeSpan) {
            postRelDate = timeSpan[0].textContent || ''
          }
        }
      }
    }
  }

  return {
    mediaType: 'reddit',
    userName: userName,
    postText: postText || '',
    postRelDate: postRelDate
  }
}

const createOldRedditTipButton = () => {
  const huhiTipButton = document.createElement('a')
  huhiTipButton.className = 'reddit-actionButton'
  huhiTipButton.href = 'javascript:void(0)'
  huhiTipButton.textContent = getMessage('redditTipsIconLabel')
  return huhiTipButton
}

const createRedditTipButton = () => {
  const huhiTipButton = document.createElement('button')
  huhiTipButton.className = 'reddit-actionButton'
  huhiTipButton.style.display = 'inline-block'
  huhiTipButton.style.transition = 'color 0.1s ease 0s'
  huhiTipButton.style.background = 'transparent'
  huhiTipButton.style.border = 'none'
  huhiTipButton.style.color = 'inherit'
  huhiTipButton.style.cursor = 'pointer'
  huhiTipButton.style.padding = '2px 10px 0 10px'
  huhiTipButton.style.borderRadius = '2px'
  huhiTipButton.style.outline = 'none'
  huhiTipButton.type = 'button'

  const style = document.createElement('style')
  style.innerHTML = '.reddit-actionButton :hover { color: #FB542B }'
  huhiTipButton.appendChild(style)

  return huhiTipButton
}

const createRedditIconContainer = () => {
  const huhiTipIconContainer = document.createElement('div')
  huhiTipIconContainer.className = 'IconContainer'
  huhiTipIconContainer.style.display = 'inline-block'
  huhiTipIconContainer.style.marginBottom = '-2px'
  huhiTipIconContainer.style.position = 'relative'
  huhiTipIconContainer.style.verticalAlign = 'middle'
  return huhiTipIconContainer
}

const createOldRedditIconContainer = () => {
  const huhiTipIconContainer = document.createElement('div')
  huhiTipIconContainer.className = 'IconContainer'
  huhiTipIconContainer.style.display = 'inline-block'
  huhiTipIconContainer.style.marginBottom = '-2px'
  huhiTipIconContainer.style.position = 'relative'
  huhiTipIconContainer.style.verticalAlign = 'middle'
  return huhiTipIconContainer
}

const createRedditTipAction = (isPost: boolean) => {
  const huhiTipAction = document.createElement('div')
  huhiTipAction.className = 'action-huhi-tip'
  if (isPost) {
    huhiTipAction.style.display = 'flex'
    huhiTipAction.style.height = '25px'
    huhiTipAction.style.outline = 'none'
    huhiTipAction.style.borderRadius = '2px'
  }
  huhiTipAction.setAttribute('data-original-title', getMessage('redditTipsHoverText'))
  return huhiTipAction
}

const createOldRedditTipAction = () => {
  const huhiTipAction = document.createElement('li')
  huhiTipAction.className = 'action-huhi-tip'
  return huhiTipAction
}

const createRedditTipIcon = () => {
  const huhiTipIcon = document.createElement('span')
  huhiTipIcon.className = 'tip-icon--medium'
  huhiTipIcon.style.background = 'transparent'
  huhiTipIcon.style.content = 'url(\'data:image/svg+xml;utf8,<svg version="1.1" id="Layer_1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px" viewBox="0 0 105 100" style="enable-background:new 0 0 105 100;" xml:space="preserve"><style type="text/css">.st1{fill:%23662D91;}.st2{fill:%239E1F63;}.st3{fill:%23FF5000;}.st4{fill:%23FFFFFF;stroke:%23FF5000;stroke-width:0.83;stroke-miterlimit:10;}</style><title>BAT_icon</title><g id="Layer_2_1_"><g id="Layer_1-2"><polygon class="st1" points="94.8,82.6 47.4,55.4 0,82.9 "/><polygon class="st2" points="47.4,0 47.1,55.4 94.8,82.6 "/><polygon class="st3" points="0,82.9 47.2,55.9 47.4,0 "/><polygon class="st4" points="47.1,33.7 28,66.5 66.7,66.5 "/></g></g></svg>\')'
  huhiTipIcon.style.display = 'inline-block'
  huhiTipIcon.style.fontSize = '18px'
  huhiTipIcon.style.fontStyle = 'normal'
  huhiTipIcon.style.height = '16px'
  huhiTipIcon.style.position = 'relative'
  huhiTipIcon.style.verticalAlign = 'baseline'
  huhiTipIcon.style.width = '16px'
  return huhiTipIcon
}

const createRedditTipActionCount = () => {
  const huhiTipActionCount = document.createElement('span')
  huhiTipActionCount.className = 'reddit-actionCount'
  huhiTipActionCount.style.color = 'inherit'
  huhiTipActionCount.style.display = 'inline-block'
  huhiTipActionCount.style.fontSize = '12px'
  huhiTipActionCount.style.fontWeight = 'bold'
  huhiTipActionCount.style.lineHeight = '1'
  huhiTipActionCount.style.marginLeft = '3px'
  huhiTipActionCount.style.position = 'relative'
  huhiTipActionCount.style.verticalAlign = 'text-bottom'
  return huhiTipActionCount
}

const createRedditTipActionCountPresentation = () => {
  const huhiTipActionCountPresentation = document.createElement('span')
  huhiTipActionCountPresentation.className = 'reddit-actionButton'
  huhiTipActionCountPresentation.textContent = getMessage('redditTipsIconLabel')
  return huhiTipActionCountPresentation
}

const createHoverStyleElement = (isPost: boolean) => {
  // Create style element for hover
  const style = document.createElement('style')
  style.innerHTML = isPost ? ':host { outline: none } :host(:hover) { background-color: var(--newRedditTheme-navIconFaded10) }' : '.reddit-actionButton { text-decoration: none; color: var(--newCommunityTheme-actionIcon); font-weight: bold; padding: 0px 1px; } .reddit-actionButton:hover { color: var(--newCommunityTheme-bodyText); text-decoration: underline }'
  return style
}

const createHoverStyleElementForOld = () => {
  const style = document.createElement('style')
  style.innerHTML = '.reddit-actionButton { color: #888; font-weight: bold; paddings: 0 1px; text-decoration: none } .reddit-actionButton:hover { text-decoration: underline }'
  return style
}

const getMoreActionCommentElement = (commentElement: Element) => {
  return commentElement.querySelector('button[aria-label="more options"]')
}

const getMoreActionPostElement = (postElement: Element) => {
  const element = postElement.querySelector('button[aria-label="more options"]')
  if (element) {
    return !element.nextElementSibling && !element.previousElementSibling && element.parentElement ? element.parentElement : element
  }
  return null
}

const getSaveElement = (commentElement: Element) => {
  return document.evaluate(".//button[text()='Save']", commentElement, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue as HTMLElement
}

const getPromotedSaveElement = (element: Element) => {
  const saveElement = document.evaluate(".//span[text()='save']", element, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue as HTMLElement
  if (saveElement && saveElement.parentElement) {
    return saveElement.parentElement
  }
  return null
}

const isUsersOwnPost = (commentElement: Element) => {
  const editElement: Node = document.evaluate(".//button[text()='edit']", commentElement, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue
  return editElement
}

const createHuhiTipActionForOld = (redditPost: Element) => {
  // Create the tip action
  const huhiTipAction = createOldRedditTipAction()

  // Create a container that is eligible to attach shadow DOM
  const huhiTipActionContainer = document.createElement('span')
  huhiTipAction.appendChild(huhiTipActionContainer)

  const huhiTipIconContainer = createOldRedditIconContainer()

  const huhiTipIcon = createRedditTipIcon()
  huhiTipIconContainer.appendChild(huhiTipIcon)

  // Create the tip button
  const huhiTipButton = createOldRedditTipButton()
  huhiTipButton.appendChild(huhiTipIconContainer)
  // Create button event
  huhiTipButton.onclick = function (event) {
    const redditMetaData = getOldRedditMetaData(redditPost)
    if (redditMetaData) {
      const msg = { type: 'tipInlineMedia', mediaMetaData: redditMetaData }
      chrome.runtime.sendMessage(msg)
    }
    event.stopPropagation()
  }

  const shadowRoot = huhiTipActionContainer.attachShadow({ mode: 'open' })
  shadowRoot.appendChild(huhiTipIconContainer)
  shadowRoot.appendChild(huhiTipButton)
  shadowRoot.appendChild(createHoverStyleElementForOld())
  return huhiTipAction
}

const createHuhiTipAction = (redditPost: Element, isPost: boolean) => {
  // Create the tip action
  const huhiTipAction = createRedditTipAction(isPost)

  // Create the tip button
  const huhiTipButton = createRedditTipButton()

  // Create button event
  huhiTipButton.onclick = function (event) {
    const redditMetaData = getRedditMetaData(redditPost)
    if (redditMetaData) {
      const msg = { type: 'tipInlineMedia', mediaMetaData: redditMetaData }
      chrome.runtime.sendMessage(msg)
    }
    event.stopPropagation()
  }

  // Create the tip icon container
  const huhiTipIconContainer = createRedditIconContainer()
  huhiTipButton.appendChild(huhiTipIconContainer)

  // Create the tip icon
  const huhiTipIcon = createRedditTipIcon()
  huhiTipIconContainer.appendChild(huhiTipIcon)

  // Create the tip action count
  const huhiTipActionCount = createRedditTipActionCount()
  huhiTipButton.appendChild(huhiTipActionCount)

  // Create the tip action count presentation
  const huhiTipActionCountPresentation = createRedditTipActionCountPresentation()
  huhiTipActionCount.appendChild(huhiTipActionCountPresentation)

  // Create the shadow DOM root
  const shadowRoot = huhiTipAction.attachShadow({ mode: 'open' })
  shadowRoot.appendChild(huhiTipButton)

  const hoverStyleElement = createHoverStyleElement(isPost)
  shadowRoot.appendChild(hoverStyleElement)

  return huhiTipAction
}

const handleConfigureForSaveElement = (element: Element, isPost: boolean, isPromoPost: boolean) => {
  const saveElement = isPromoPost ? getPromotedSaveElement(element) : getSaveElement(element)
  if (saveElement) {
    saveElement.insertAdjacentElement(
      'afterend', createHuhiTipAction(element, isPost))
  }
}

const handleConfigureForMoreInfoElement = (element: Element, lastElement: Element, isPost: boolean, isUsersPost: boolean) => {
  if (!isUsersPost) {
    lastElement.insertAdjacentElement(
      'beforebegin', createHuhiTipAction(element, isPost))
  } else if (lastElement.parentElement && isUsersPost) {
    lastElement.parentElement.insertAdjacentElement(
      'beforebegin', createHuhiTipAction(element, isPost))
  }
}

const configureForPosts = (rewardsEnabled: boolean, inlineTipEnabled: boolean, isForPosts: boolean, isForPromotedPosts: boolean) => {
  // special case -- use this for promoted content when user isn't logged in
  const postElements = isForPosts ? document.getElementsByClassName('Post') : document.getElementsByClassName('Comment')
  for (let ix = 0; ix < postElements.length; ix++) {
    const isUsersPost = isUsersOwnPost(postElements[ix])
    const actions = postElements[ix].querySelectorAll('div.action-huhi-tip')
    const inEditModeElements = postElements[ix].querySelector('div[data-test-id="comment-submission-form-richtext"')
    if (rewardsEnabled && inlineTipEnabled && actions && actions.length === 0 && !inEditModeElements) {
      const lastElement = isForPosts ? getMoreActionPostElement(postElements[ix]) : getMoreActionCommentElement(postElements[ix])
      if (lastElement) {
        handleConfigureForMoreInfoElement(postElements[ix], lastElement, isForPosts, !!isUsersPost)
      } else {
        handleConfigureForSaveElement(postElements[ix], isForPosts, isForPromotedPosts)
      }
    }
  }
}

const configureForOldReddit = (rewardsEnabled: boolean, inlineTipEnabled: boolean, postType: string) => {
  const elements = document.querySelectorAll('div[data-type="' + postType + '"]')
  for (let ix = 0; ix < elements.length; ix++) {
    const actions = elements[ix].querySelectorAll('li.action-huhi-tip')
    if (rewardsEnabled && inlineTipEnabled && actions && actions.length === 0) {
      const ulElement = elements[ix].getElementsByClassName('flat-list')
      if (ulElement && ulElement.length !== 0) {
        ulElement[0].insertAdjacentElement('beforeend', createHuhiTipActionForOld(elements[ix]))
      }
    }
  }
}

const configureRedditTipAction = (rewardsEnabled: boolean, inlineTipEnabled: boolean, isOldReddit: boolean) => {
  if (isOldReddit) {
    // for comments, replies, etc
    configureForOldReddit(rewardsEnabled, inlineTipEnabled, 'comment')

    // for initial posts, etc
    configureForOldReddit(rewardsEnabled, inlineTipEnabled, 'link')
  } else {
    // for comments, replies, etc
    configureForPosts(rewardsEnabled, inlineTipEnabled, false, false)

    // for initial posts
    configureForPosts(rewardsEnabled, inlineTipEnabled, true, false)

    // for promoted posts (on feeds)
    configureForPosts(rewardsEnabled, inlineTipEnabled, true, true)
  }
}

const configureHuhiTipAction = () => {
  clearTimeout(timeout)
  chrome.runtime.sendMessage('rewardsEnabled', function (rewards) {
    const msg = {
      type: 'inlineTippingPlatformEnabled',
      key: 'reddit'
    }
    chrome.runtime.sendMessage(msg, function (inlineTip) {
      configureRedditTipAction(rewards.enabled, inlineTip.enabled, isOldReddit())
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

configureHuhiTipAction()
