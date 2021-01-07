/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_BAT_GET_MEDIA_H_
#define HUHILEDGER_BAT_GET_MEDIA_H_

#include <string>
#include <map>
#include <memory>

#include "bat/ledger/internal/legacy/media/github.h"
#include "bat/ledger/internal/legacy/media/reddit.h"
#include "bat/ledger/internal/legacy/media/twitch.h"
#include "bat/ledger/internal/legacy/media/vimeo.h"
#include "bat/ledger/internal/legacy/media/youtube.h"
#include "bat/ledger/ledger.h"

namespace ledger {
class LedgerImpl;
}

namespace huhiledger_media {

class Media {
 public:
  explicit Media(ledger::LedgerImpl* ledger);

  ~Media();

  static std::string GetLinkType(const std::string& url,
                                 const std::string& first_party_url,
                                 const std::string& referrer);

  void ProcessMedia(const std::map<std::string, std::string>& parts,
                    const std::string& type,
                    ledger::type::VisitDataPtr visit_data);

  void GetMediaActivityFromUrl(uint64_t windowId,
                               ledger::type::VisitDataPtr visit_data,
                               const std::string& type,
                               const std::string& publisher_blob);

  void SaveMediaInfo(const std::string& type,
                     const std::map<std::string, std::string>& data,
                     ledger::PublisherInfoCallback callback);

  static std::string GetShareURL(
      const std::string& type,
      const std::map<std::string, std::string>& args);

 private:
  void OnMediaActivityError(ledger::type::VisitDataPtr visit_data,
                          const std::string& type,
                          uint64_t windowId);

  ledger::LedgerImpl* ledger_;  // NOT OWNED
  std::unique_ptr<huhiledger_media::YouTube> media_youtube_;
  std::unique_ptr<huhiledger_media::Twitch> media_twitch_;
  std::unique_ptr<huhiledger_media::Reddit> media_reddit_;
  std::unique_ptr<huhiledger_media::Vimeo> media_vimeo_;
  std::unique_ptr<huhiledger_media::GitHub> media_github_;
};

}  // namespace huhiledger_media

#endif  // HUHILEDGER_BAT_GET_MEDIA_H_
