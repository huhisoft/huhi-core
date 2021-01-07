/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_SPEEDREADER_SPEEDREADER_REWRITER_SERVICE_H_
#define HUHI_COMPONENTS_SPEEDREADER_SPEEDREADER_REWRITER_SERVICE_H_

#include <memory>
#include <string>

#include "base/memory/weak_ptr.h"
#include "huhi/components/huhi_component_updater/browser/huhi_component.h"
#include "huhi/components/huhi_component_updater/browser/dat_file_util.h"
#include "huhi/components/speedreader/speedreader_component.h"

namespace base {
class FilePath;
}

namespace speedreader {
class SpeedReader;
class Rewriter;
}  // namespace speedreader

class GURL;

namespace speedreader {

class SpeedreaderRewriterService : public SpeedreaderComponent::Observer {
 public:
  // SpeedreaderComponent::Observer
  void OnWhitelistReady(const base::FilePath& path) override;
  void OnStylesheetReady(const base::FilePath& path) override;

  explicit SpeedreaderRewriterService(
      huhi_component_updater::HuhiComponent::Delegate* delegate);
  ~SpeedreaderRewriterService() override;

  SpeedreaderRewriterService(const SpeedreaderRewriterService&) = delete;
  SpeedreaderRewriterService& operator=(const SpeedreaderRewriterService&) =
      delete;

  // The API
  bool IsWhitelisted(const GURL& url);
  std::unique_ptr<Rewriter> MakeRewriter(const GURL& url);
  const std::string& GetContentStylesheet();

 private:
  using GetDATFileDataResult =
      huhi_component_updater::LoadDATFileDataResult<speedreader::SpeedReader>;

  void OnLoadDATFileData(GetDATFileDataResult result);
  void OnLoadStylesheet(std::string stylesheet);

  std::string content_stylesheet_;
  std::unique_ptr<speedreader::SpeedreaderComponent> component_;
  std::unique_ptr<speedreader::SpeedReader> speedreader_;
  base::WeakPtrFactory<SpeedreaderRewriterService> weak_factory_{this};
};

}  // namespace speedreader

#endif  // HUHI_COMPONENTS_SPEEDREADER_SPEEDREADER_REWRITER_SERVICE_H_
