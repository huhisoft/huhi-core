/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * @TODO HuyNQ link appstore, ch play, link share social media
 * */

import AppStoreFavicon from '../../img/newtab/defaultTopSitesIcon/appstore.png'
import HuhiFavicon from '../../img/newtab/defaultTopSitesIcon/huhi.png'
import FacebookFavicon from '../../img/newtab/defaultTopSitesIcon/facebook.png'
import PlayStoreFavicon from '../../img/newtab/defaultTopSitesIcon/playstore.png'
import TwitterFavicon from '../../img/newtab/defaultTopSitesIcon/twitter.png'
import YouTubeFavicon from '../../img/newtab/defaultTopSitesIcon/youtube.png'

export const defaultTopSitesData = [
  {
    name: 'App Store',
    url: 'https://itunes.apple.com/app/huhi-browser/id20061990?mt=8',
    favicon: AppStoreFavicon,
    background: 'rgba(255,255,255,0.8)'
  },
  {
    name: 'Huhi Software',
    url: 'https://huhisoft.com',
    favicon: HuhiFavicon,
    background: 'rgba(255,255,255,0.8)'
  },
  {
    name: 'Facebook',
    url: 'https://www.facebook.com/HuhiSoftware/',
    favicon: FacebookFavicon,
    background: 'rgba(255,255,255,0.8)'
  },
  {
    name: 'Play Store',
    url: 'https://play.google.com/store/apps/details?id=com.huhi.browser&hl=en_US',
    favicon: PlayStoreFavicon,
    background: 'rgba(255,255,255,0.8)'
  },
  {
    name: 'Twitter',
    url: 'https://twitter.com/huhibrowser',
    favicon: TwitterFavicon,
    background: 'rgba(255,255,255,0.8)'
  },
  {
    name: 'YouTube',
    url: 'https://www.youtube.com/huhibrowser',
    favicon: YouTubeFavicon,
    background: 'rgba(255,255,255,0.8)'
  }
]
