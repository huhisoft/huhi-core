/* This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_TOOLBAR_TOOLBAR_ACTIONS_MODEL_H_
#define HUHI_BROWSER_UI_TOOLBAR_TOOLBAR_ACTIONS_MODEL_H_

#include "chrome/browser/ui/toolbar/toolbar_actions_model.h"

namespace extensions {
class Extension;
}

// The purposes of this subclass are to:
// - Hide the Huhi 'extension' item from the |ToolbarActionsBar|, since it is
//   displayed in the |HuhiActionsContainer|
class HuhiToolbarActionsModel : public ToolbarActionsModel {
  public:
    using ToolbarActionsModel::ToolbarActionsModel;
    bool ShouldAddExtension(const extensions::Extension* extension) override;
  private:
    DISALLOW_COPY_AND_ASSIGN(HuhiToolbarActionsModel);
};

#endif