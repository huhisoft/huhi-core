/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import ITheme from 'huhi-ui/theme/theme-interface'
import darkTheme from 'huhi-ui/theme/huhi-dark'
import colors from 'huhi-ui/theme/colors'

const shieldsDarkTheme: ITheme = {
  ...darkTheme,
  name: 'Shields Dark',
  color: {
    ...darkTheme.color,
    lionLogo: colors.grey700,
    text: colors.white,
    panelBackground: '#17171F',
    panelBackgroundSecondary: colors.grey900,
    inputBorder: colors.grey700,
    separatorLine: colors.grey800,
    modalOverlayBackground: 'rgba(33, 37, 41, 70%)'
  }
}

export default shieldsDarkTheme
