
/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// Utils
import { getMessage } from '../background/api/locale_api'

let timeout: any = null

const tipActionCountClass = 'GitHubTip-actionCount'
const tipIconContainerClass = 'IconContainer'
const actionTipClass = 'action-huhi-tip'

const createHuhiTipAction = (elem: Element, getMetaData: (elem: Element) => RewardsTip.MediaMetaData | null) => {
  const hoverClasses = ' tooltipped tooltipped-sw tooltipped-align-right-1'

  // Create the tip action
  const huhiTipAction = document.createElement('div')
  huhiTipAction.className = 'GitHubTip-action js-tooltip ' + actionTipClass + hoverClasses
  huhiTipAction.style.display = 'inline-block'
  huhiTipAction.style.minWidth = '40px'
  huhiTipAction.setAttribute('aria-label', getMessage('githubTipsHoverText'))

  // Create the tip button
  const huhiTipButton = document.createElement('button')
  huhiTipButton.className = 'GitHubTip-actionButton u-textUserColorHover js-actionButton'
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
    const githubMetaData = getMetaData(elem)
    if (githubMetaData) {
      const msg = { type: 'tipInlineMedia', mediaMetaData: githubMetaData }
      chrome.runtime.sendMessage(msg)
    }
    event.stopPropagation()
  }

  // Create the tip icon container
  const huhiTipIconContainer = document.createElement('div')
  huhiTipIconContainer.className = tipIconContainerClass + ' js-tooltip'
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
  huhiTipActionCount.className = tipActionCountClass
  huhiTipActionCount.style.color = '#657786'
  huhiTipActionCount.style.display = 'inline-block'
  huhiTipActionCount.style.fontSize = '12px'
  huhiTipActionCount.style.fontWeight = 'bold'
  huhiTipActionCount.style.lineHeight = '1'
  huhiTipActionCount.style.marginLeft = '1px'
  huhiTipActionCount.style.position = 'relative'
  huhiTipActionCount.style.verticalAlign = 'text-bottom'
  huhiTipButton.appendChild(huhiTipActionCount)

  // Create the tip action count presentation
  const huhiTipActionCountPresentation = document.createElement('span')
  huhiTipActionCountPresentation.className = 'GitHubTip-actionCountForPresentation'
  huhiTipActionCountPresentation.textContent = getMessage('githubTipsIconLabel')
  huhiTipActionCount.appendChild(huhiTipActionCountPresentation)

  // Create the shadow DOM root that hosts our injected DOM elements
  const shadowRoot = huhiTipAction.attachShadow({ mode: 'open' })
  shadowRoot.appendChild(huhiTipButton)

  // Create style element for hover color
  const style = document.createElement('style')
  style.innerHTML = '.GitHubTip-actionButton :hover { color: #FB542B }'
  shadowRoot.appendChild(style)

  return huhiTipAction
}

const getQueryStringVal = (key: string, queryString: string): string | null => {
  const match = queryString.match(`[\?|&]${key}=([^&]+)&?`)
  return match && match[1]
}

const isBlackListTab = (queryString: string) => {
  const blackList = ['repositories']
  const tab = getQueryStringVal('tab', queryString)
  if (!tab || blackList.includes(tab)) { // Don't inject on overview tab
    return true
  }
  return false
}

const getCommentMetaData = (elem: Element): RewardsTip.MediaMetaData | null => {
  let ancestor = elem.closest('.timeline-comment-header')
  ancestor = ancestor ? ancestor : elem.closest('.review-comment')
  if (ancestor) {
    const authorCollection = ancestor.getElementsByClassName('author')
    if (authorCollection.length) {
      const author = authorCollection[0] as HTMLElement
      const userName = author.innerHTML
      return {
        mediaType: 'github',
        userName: userName || ''
      }
    }
  }
  return null
}

const commentInsertFunction = (parent: Element) => {
  const tipElem = createHuhiTipAction(parent, getCommentMetaData)
  if (tipElem.shadowRoot) {
    let iconContainer = tipElem.shadowRoot.querySelectorAll('.' + tipIconContainerClass)[0] as HTMLElement
    let huhiTipActionCount = tipElem.shadowRoot.querySelectorAll('.' + tipActionCountClass)[0] as HTMLElement
    iconContainer.style.paddingBottom = '5px'
    huhiTipActionCount.style.paddingBottom = '2px'
    tipElem.style.marginRight = '2px'
  }
  const children = parent.childNodes
  if (children.length > 1) {
    const end = children[children.length - 2]
    parent.insertBefore(tipElem, end)
  }
}

const getReviewItemMetaData = (elem: Element): RewardsTip.MediaMetaData | null => {
  const ancestor = elem.closest('.discussion-item')
  if (ancestor) {
    const authorCollection = ancestor.getElementsByClassName('author')
    if (authorCollection.length) {
      const author = authorCollection[0] as HTMLElement
      const userName = author.innerHTML
      return {
        mediaType: 'github',
        userName: userName || ''
      }
    }
  }
  return null
}

const reviewItemInsertFunction = (parent: Element) => {
  const tipLocation = parent.getElementsByClassName('discussion-item-copy')[0]
  if (tipLocation) {
    const tipElem = createHuhiTipAction(tipLocation, getReviewItemMetaData)
    if (tipElem.shadowRoot) {
      const iconContainerCollection = tipElem.shadowRoot.querySelectorAll('.' + tipIconContainerClass)
      const huhiTipActionCountCollection = tipElem.shadowRoot.querySelectorAll('.' + tipActionCountClass)
      if (iconContainerCollection.length && huhiTipActionCountCollection.length) {
        const iconContainer = iconContainerCollection[0] as HTMLElement
        const huhiTipActionCount = huhiTipActionCountCollection[0] as HTMLElement
        iconContainer.style.paddingBottom = '5px'
        huhiTipActionCount.style.paddingBottom = '2px'
      }
    }
    tipLocation.appendChild(tipElem)
  }
}

const getCommitLinksMetaData = (elem: Element): RewardsTip.MediaMetaData | null => {
  const ancestor = elem.closest('.commit')
  if (ancestor) {
    const avatarCollection = ancestor.getElementsByClassName('avatar')
    if (avatarCollection.length) {
      const avatar = avatarCollection[0] as HTMLElement
      const avatarChildren = avatar.children
      if (avatarChildren.length) {
        const userName = (avatarChildren[0] as HTMLImageElement).alt.slice(1)
        return {
          mediaType: 'github',
          userName: userName || ''
        }
      }
    }
  }
  return null
}

const commitLinksInsertFunction = (parent: Element) => {
  const tipElem = createHuhiTipAction(parent, getCommitLinksMetaData)
  tipElem.style.marginLeft = '9px'
  parent.appendChild(tipElem)
}

const getStarringContainerMetaData = (elem: Element): RewardsTip.MediaMetaData | null => {
  const ancestor = elem.closest('.d-block')
  if (ancestor) {
    const aTags = ancestor.getElementsByTagName('A')
    if (aTags.length) {
      const aTag = aTags[0] as HTMLAnchorElement
      if (aTag.href) {
        const split = aTag.href.split('/')
        if (split.length > 3) {
          const userName = split[3]
          return {
            mediaType: 'github',
            userName: userName || ''
          }
        }
      }
    }
  }
  return null
}

const starringContainerInsertFunction = (parent: Element) => {
  if (isBlackListTab(window.location.search)) {
    return
  }
  const correctSubclass = 'starring-container'
  if (!parent.getElementsByClassName(correctSubclass).length) {
    return
  }
  const subElem = parent.getElementsByClassName(correctSubclass)[0]
  const tipElem = createHuhiTipAction(parent, getStarringContainerMetaData)
  tipElem.classList.add('d-inline-block')
  tipElem.style.minWidth = '60px'
  parent.insertBefore(tipElem, subElem)
}

const getPageHeadMetaData = (elem: Element): RewardsTip.MediaMetaData | null => {
  const elems = document.getElementsByClassName('gisthead')
  if (elems.length) {
    elem = elems[0]
    const authors = elem.getElementsByClassName('author')
    if (authors.length) {
      const author = authors[0]
      const aTags = author.getElementsByTagName('A')
      if (aTags.length) {
        const aTag = aTags[0] as HTMLAnchorElement
        const userName = aTag.innerHTML
        return {
          mediaType: 'github',
          userName: userName || ''
        }
      }
    }
  }
  return null
}

const pageheadInsertFunction = (parent: Element) => {
  const subdomain = window.location.host.split('.')[0]
  if (subdomain === 'gist' &&
      window.location.pathname.slice(1).split('/').length > 1) {
    const tipElem = createHuhiTipAction(parent, getPageHeadMetaData)
    parent.appendChild(tipElem)
  }
}

const getMemberListItemMetaData = (elem: Element): RewardsTip.MediaMetaData | null => {
  const ancestor = elem.closest('.table-list-cell')
  if (ancestor) {
    const aTags = ancestor.getElementsByTagName('A')
    if (aTags.length) {
      const aTag = aTags[0] as HTMLAnchorElement
      if (aTag.href) {
        const split = aTag.href.split('/')
        if (split.length > 3) {
          const userName = split[3]
          return {
            mediaType: 'github',
            userName: userName || ''
          }
        }
      }
    }
  }
  return null
}

const memberListItemInsertFunction = (parent: Element) => {
  if (parent.children.length > 1) {
    const path = window.location.pathname
    const memberText = parent.children[1] as HTMLElement
    const tipElem = createHuhiTipAction(memberText as Element, getMemberListItemMetaData)
    if (!memberText || path.startsWith('/orgs/')) {
      return
    }
    tipElem.style.paddingLeft = '5px'
    if (path.split('/').includes('teams')) { // Special case, different styling for same element
      memberText.appendChild(tipElem)
    } else {
      memberText.style.width = '250px'
      if (memberText.children.length) {
        memberText.insertBefore(tipElem, memberText.children[1])
      }
    }
  }
}

const commentParentClass = 'timeline-comment-actions'
const reviewItemParentClass = 'discussion-item-review'
const commitLinksParentClass = 'commit-links-cell'
const starringContainerParentClass = 'float-right'
const pageHeadParentClass = 'pagehead-actions'
const memberListItemParentClass = 'member-list-item'

const configureGitHubTipAction = (tipLocationClass: string, tippingEnabled: boolean,
      insertFunction: (parent: Element) => void) => {
  const tipLocations = document.getElementsByClassName(tipLocationClass)
  for (let i = 0; i < tipLocations.length; ++i) {
    const parent = tipLocations[i]
    if (parent) {
      const huhiTipActions = parent.getElementsByClassName(actionTipClass)
      if (tippingEnabled && huhiTipActions.length === 0) {
        insertFunction(parent)
      } else if (!tippingEnabled && huhiTipActions.length === 1) {
        const attachedParent = huhiTipActions[0].parentElement
        if (attachedParent) {
          attachedParent.removeChild(huhiTipActions[0])
        }
      }
    }
  }
}

const configureGitHubTipActions = (tippingEnabled: boolean) => {
  let tipLocationClasses = [commentParentClass,
    reviewItemParentClass,
    commitLinksParentClass,
    starringContainerParentClass,
    pageHeadParentClass,
    memberListItemParentClass
  ]

  let insertFunctions = [commentInsertFunction,
    reviewItemInsertFunction,
    commitLinksInsertFunction,
    starringContainerInsertFunction,
    pageheadInsertFunction,
    memberListItemInsertFunction
  ]

  for (let i in tipLocationClasses) {
    configureGitHubTipAction(tipLocationClasses[i], tippingEnabled, insertFunctions[i])
  }
}

const configureHuhiTipAction = () => {
  clearTimeout(timeout)
  chrome.runtime.sendMessage('rewardsEnabled', function (rewards) {
    const msg = {
      type: 'inlineTippingPlatformEnabled',
      key: 'github'
    }
    chrome.runtime.sendMessage(msg, function (inlineTip) {
      let tippingEnabled = rewards.enabled && inlineTip.enabled
      configureGitHubTipActions(tippingEnabled)
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
