/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <memory>
#include <utility>

#include "bat/ledger/internal/ledger_impl.h"
#include "bat/ledger/internal/legacy/media/media.h"
#include "bat/ledger/internal/legacy/static_values.h"
#include "bat/ledger/internal/constants.h"

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

namespace huhiledger_media {

Media::Media(ledger::LedgerImpl* ledger):
  ledger_(ledger),
  media_youtube_(new huhiledger_media::YouTube(ledger)),
  media_twitch_(new huhiledger_media::Twitch(ledger)),
  media_twitter_(new huhiledger_media::Twitter(ledger)),
  media_reddit_(new huhiledger_media::Reddit(ledger)),
  media_vimeo_(new huhiledger_media::Vimeo(ledger)),
  media_github_(new huhiledger_media::GitHub(ledger)) {
}  // namespace huhiledger_media

Media::~Media() {}

// static
std::string Media::GetLinkType(
    const std::string& url,
    const std::string& first_party_url,
    const std::string& referrer) {
  std::string type;
  type = huhiledger_media::YouTube::GetLinkType(url);

  if (type.empty()) {
    type = huhiledger_media::Twitch::GetLinkType(
        url,
        first_party_url,
        referrer);
  }

  if (type.empty()) {
    type = huhiledger_media::Vimeo::GetLinkType(url);
  }

  if (type.empty()) {
    type = huhiledger_media::GitHub::GetLinkType(url);
  }

  return type;
}

void Media::ProcessMedia(
    const std::map<std::string, std::string>& parts,
    const std::string& type,
    ledger::type::VisitDataPtr visit_data) {
  if (parts.empty() ||
      !ledger_->state()->GetRewardsMainEnabled() ||
      !visit_data) {
    return;
  }

  if (type == YOUTUBE_MEDIA_TYPE) {
    media_youtube_->ProcessMedia(parts, *visit_data);
    return;
  }

  if (type == TWITCH_MEDIA_TYPE) {
    media_twitch_->ProcessMedia(parts, *visit_data);
    return;
  }

  if (type == VIMEO_MEDIA_TYPE) {
    media_vimeo_->ProcessMedia(parts);
    return;
  }

  if (type == GITHUB_MEDIA_TYPE) {
    media_github_->ProcessMedia(parts, *visit_data);
    return;
  }
}

void Media::GetMediaActivityFromUrl(
    uint64_t window_id,
    ledger::type::VisitDataPtr visit_data,
    const std::string& type,
    const std::string& publisher_blob) {
  if (type == YOUTUBE_MEDIA_TYPE) {
    media_youtube_->ProcessActivityFromUrl(window_id, *visit_data);
  } else if (type == TWITCH_MEDIA_TYPE) {
    media_twitch_->ProcessActivityFromUrl(window_id,
                                          *visit_data,
                                          publisher_blob);
  } else if (type == TWITTER_MEDIA_TYPE) {
    media_twitter_->ProcessActivityFromUrl(window_id,
                                           *visit_data);
  } else if (type == REDDIT_MEDIA_TYPE) {
    media_reddit_->ProcessActivityFromUrl(window_id, *visit_data);
  } else if (type == VIMEO_MEDIA_TYPE) {
    media_vimeo_->ProcessActivityFromUrl(window_id, *visit_data);
  } else if (type == GITHUB_MEDIA_TYPE) {
    media_github_->ProcessActivityFromUrl(window_id, *visit_data);
  } else {
    OnMediaActivityError(std::move(visit_data), type, window_id);
  }
}

void Media::OnMediaActivityError(ledger::type::VisitDataPtr visit_data,
                                       const std::string& type,
                                       uint64_t window_id) {
  std::string url;
  std::string name;
  if (type == YOUTUBE_MEDIA_TYPE) {
    url = YOUTUBE_TLD;
    name = YOUTUBE_MEDIA_TYPE;
  } else if (type == TWITCH_MEDIA_TYPE) {
    url = TWITCH_TLD;
    name = TWITCH_MEDIA_TYPE;
  } else if (type == TWITTER_MEDIA_TYPE) {
    url = TWITTER_TLD;
    name = TWITTER_MEDIA_TYPE;
  } else if (type == REDDIT_MEDIA_TYPE) {
    url = REDDIT_TLD;
    name = REDDIT_MEDIA_TYPE;
  } else if (type == VIMEO_MEDIA_TYPE) {
    url = VIMEO_TLD;
    name = VIMEO_MEDIA_TYPE;
  }

  if (url.empty()) {
    BLOG(0, "Media activity error for url: " << visit_data->url);
    return;
  }

  visit_data->domain = url;
  visit_data->url = "https://" + url;
  visit_data->path = "/";
  visit_data->name = name;

  ledger_->publisher()->GetPublisherActivityFromUrl(
      window_id,
      std::move(visit_data),
      "");
}

void Media::SaveMediaInfo(const std::string& type,
                                const std::map<std::string, std::string>& data,
                                ledger::PublisherInfoCallback callback) {
  if (type == TWITTER_MEDIA_TYPE) {
    media_twitter_->SaveMediaInfo(data, callback);
    return;
  } else if (type == REDDIT_MEDIA_TYPE) {
    media_reddit_->SaveMediaInfo(data, callback);
    return;
  }
  if (type == GITHUB_MEDIA_TYPE) {
    media_github_->SaveMediaInfo(data, callback);
    return;
  }
}

// static
std::string Media::GetShareURL(
    const std::string& type,
    const std::map<std::string, std::string>& args) {
  if (type == TWITTER_MEDIA_TYPE) {
    return huhiledger_media::Twitter::GetShareURL(args);
  }

  return std::string();
}
}  // namespace huhiledger_media
