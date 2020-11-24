/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <vector>

#include "components/permissions/permission_request.h"
#include "third_party/widevine/cdm/buildflags.h"
#include "ui/views/bubble/bubble_dialog_delegate_view.h"
#include "ui/views/window/dialog_delegate.h"

#if BUILDFLAG(ENABLE_WIDEVINE)
#include "huhi/browser/widevine/widevine_permission_request.h"
#include "huhi/grit/huhi_generated_resources.h"
#include "chrome/browser/ui/views/chrome_layout_provider.h"
#include "ui/gfx/text_constants.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/views/controls/button/checkbox.h"
#include "ui/views/controls/label.h"
#include "ui/views/style/typography.h"
#endif

namespace {

#if BUILDFLAG(ENABLE_WIDEVINE)
class DontAskAgainCheckbox : public views::Checkbox,
                             public views::ButtonListener {
 public:
  explicit DontAskAgainCheckbox(WidevinePermissionRequest* request);

 private:
  // views::ButtonListener overrides:
  void ButtonPressed(Button* sender, const ui::Event& event) override;

  WidevinePermissionRequest* request_;

  DISALLOW_COPY_AND_ASSIGN(DontAskAgainCheckbox);
};

DontAskAgainCheckbox::DontAskAgainCheckbox(WidevinePermissionRequest* request)
    : Checkbox(l10n_util::GetStringUTF16(IDS_WIDEVINE_DONT_ASK_AGAIN_CHECKBOX),
               this),
      request_(request) {
}

void DontAskAgainCheckbox::ButtonPressed(Button* sender,
                                         const ui::Event& event) {
  request_->set_dont_ask_widevine_install(GetChecked());
}

bool HasWidevinePermissionRequest(
    const std::vector<permissions::PermissionRequest*>& requests) {
  // When widevine permission is requested, |requests| only includes Widevine
  // permission because it is not a candidate for grouping.
  if (requests.size() == 1 &&
      requests[0]->GetPermissionRequestType() ==
          permissions::PermissionRequestType::PERMISSION_WIDEVINE)
    return true;

  return false;
}

void AddAdditionalWidevineViewControlsIfNeeded(
    views::BubbleDialogDelegateView* dialog_delegate_view,
    const std::vector<permissions::PermissionRequest*>& requests) {
  if (!HasWidevinePermissionRequest(requests))
    return;

  auto* widevine_request = static_cast<WidevinePermissionRequest*>(requests[0]);
  views::Label* text = new views::Label(
      widevine_request->GetExplanatoryMessageText(),
      views::style::CONTEXT_LABEL, views::style::STYLE_SECONDARY);
  text->SetMultiLine(true);
  text->SetHorizontalAlignment(gfx::ALIGN_LEFT);

  ChromeLayoutProvider* provider = ChromeLayoutProvider::Get();
  const int preferred_dialog_width = provider->GetSnappedDialogWidth(
      dialog_delegate_view->GetPreferredSize().width());
  // Resize width. Then, it's height deduced.
  text->SizeToFit(preferred_dialog_width -
                  dialog_delegate_view->margins().width());
  dialog_delegate_view->AddChildView(text);
  dialog_delegate_view->AddChildView(
      new DontAskAgainCheckbox(widevine_request));
}
#else
void AddAdditionalWidevineViewControlsIfNeeded(
    views::BubbleDialogDelegateView* dialog_delegate_view,
    const std::vector<permissions::PermissionRequest*>& requests) {}
#endif
}  // namespace

#define HUHI_PERMISSION_PROMPT_BUBBLE_VIEW \
  AddAdditionalWidevineViewControlsIfNeeded(this, delegate_->Requests());

#include "../../../../../../../chrome/browser/ui/views/permission_bubble/permission_prompt_bubble_view.cc"
#undef HUHI_PERMISSION_PROMPT_BUBBLE_VIEW
