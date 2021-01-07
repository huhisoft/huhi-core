// Copyright (c) 2020 The Huhi Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import * as React from 'react'
import * as HuhiTodayElement from './default'
import CardIntro from './cards/cardIntro'
import CardLoading from './cards/cardLoading'
import { ReadFeedItemPayload } from '../../../actions/today_actions'
const Content = React.lazy(() => import('./content'))

type State = {
  hasInteractionStarted: boolean
}

export type OnReadFeedItem = (args: ReadFeedItemPayload) => any
export type OnSetPublisherPref = (publisherId: string, enabled: boolean) => any

export type Props = {
  isFetching: boolean
  isUpdateAvailable: boolean
  feed?: HuhiToday.Feed
  publishers?: HuhiToday.Publishers
  articleToScrollTo?: HuhiToday.FeedItem
  displayedPageCount: number
  onInteracting: (interacting: boolean) => any
  onReadFeedItem: OnReadFeedItem
  onFeedItemViewedCountChanged: (feedItemsViewed: number) => any
  onSetPublisherPref: OnSetPublisherPref
  onAnotherPageNeeded: () => any
  onCustomizeHuhiToday: () => any
  onRefresh: () => any
  onCheckForUpdate: () => any
}

export const attributeNameCardCount = 'data-today-card-count'

class HuhiToday extends React.PureComponent<Props, State> {
  huhiTodayHitsViewportObserver: IntersectionObserver
  scrollTriggerToFocusHuhiToday: any // React.RefObject<any>

  state = {
    hasInteractionStarted: false
  }

  componentDidMount () {
    const options = { root: null, rootMargin: '0px', threshold: 0.25 }

    this.huhiTodayHitsViewportObserver = new
      IntersectionObserver(this.handleHuhiTodayHitsViewportObserver, options)

    // Handle first card showing up so we can hide secondary UI
    this.huhiTodayHitsViewportObserver.observe(this.scrollTriggerToFocusHuhiToday)
  }

  handleHuhiTodayHitsViewportObserver = (entries: IntersectionObserverEntry[]) => {
    const isIntersecting = entries.some(entry => entry.isIntersecting)
    this.props.onInteracting(isIntersecting)
    if (isIntersecting) {
      this.setState({ hasInteractionStarted: true })
    }
  }

  render () {
    const shouldDisplayContent =
      this.state.hasInteractionStarted ||
      !!this.props.articleToScrollTo

    return (
      <HuhiTodayElement.Section>
        <div
          ref={scrollTrigger => (this.scrollTriggerToFocusHuhiToday = scrollTrigger)}
          style={{ position: 'sticky', top: '100px' }}
        />

        <CardIntro />

        { shouldDisplayContent &&
        <React.Suspense fallback={(<CardLoading />)}>
          <Content {...this.props} />
        </React.Suspense>
        }

      </HuhiTodayElement.Section>
    )
  }
}

export default HuhiToday
