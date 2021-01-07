// Copyright (c) 2020 The Huhi Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { getLocale } from '../../../../../common/locale'
import * as Card from '../cardIntro'
import HuhiTodayLogo from '../huhiTodayLogo.svg'

class HeaderBlock extends React.PureComponent<{}, {}> {
  render () {
    return (
      <Card.Intro>
        <Card.Image src={HuhiTodayLogo} />
        <Card.Heading>{getLocale('huhiTodayIntroTitle')}</Card.Heading>
        <Card.Text>{getLocale('huhiTodayIntroDescription')}</Card.Text>
      </Card.Intro>
    )
  }
}

export default HeaderBlock
