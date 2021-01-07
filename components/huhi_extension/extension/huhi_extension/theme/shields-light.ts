/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import ITheme from 'huhi-ui/theme/theme-interface'
import defaultTheme from 'huhi-ui/theme/huhi-default'
import colors from 'huhi-ui/theme/colors'

const shieldsLightTheme: ITheme = {
  ...defaultTheme,
  name: 'Shields Light',
  color: {
    ...defaultTheme.color,
    text: colors.neutral900,
    panelBackgroundSecondary: colors.neutral000,
    modalOverlayBackground: 'rgba(255, 255, 255, 70%)'
  }
}

export default shieldsLightTheme
