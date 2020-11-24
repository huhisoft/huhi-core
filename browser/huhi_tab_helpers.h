/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_HUHI_TAB_HELPERS_H_
#define HUHI_BROWSER_HUHI_TAB_HELPERS_H_

namespace content {
class WebContents;
}

namespace huhi {

void AttachTabHelpers(content::WebContents* web_contents);

}  // namespace huhi

#endif  // HUHI_BROWSER_HUHI_TAB_HELPERS_H_

