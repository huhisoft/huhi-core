/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/client/preferences/filtered_ad.h"

#include "bat/ads/internal/logging.h"
#include "bat/ads/internal/json_helper.h"

namespace ads {

FilteredAd::FilteredAd() = default;

FilteredAd::FilteredAd(
    const FilteredAd& ad) = default;

FilteredAd::~FilteredAd() = default;

std::string FilteredAd::ToJson() const {
  std::string json;
  SaveToJson(*this, &json);
  return json;
}

Result FilteredAd::FromJson(
    const std::string& json) {
  rapidjson::Document document;
  document.Parse(json.c_str());

  if (document.HasParseError()) {
    BLOG(1, helper::JSON::GetLastError(&document));
    return FAILED;
  }

  if (document.HasMember("uuid")) {
    creative_instance_id = document["uuid"].GetString();
  }

  if (document.HasMember("creative_set_id")) {
    creative_set_id = document["creative_set_id"].GetString();
  }

  return SUCCESS;
}

void SaveToJson(
    JsonWriter* writer,
    const FilteredAd& ad) {
  writer->StartObject();

  writer->String("uuid");
  writer->String(ad.creative_instance_id.c_str());

  writer->String("creative_set_id");
  writer->String(ad.creative_set_id.c_str());

  writer->EndObject();
}

}  // namespace ads
