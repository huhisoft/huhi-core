/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/common/extensions/huhi_extensions_api_provider.h"

#include "huhi/common/extensions/api/generated_includes.h"
#include "extensions/common/features/json_feature_provider_source.h"
#include "extensions/common/permissions/permissions_info.h"

namespace extensions {

HuhiExtensionsAPIProvider::HuhiExtensionsAPIProvider() {}
HuhiExtensionsAPIProvider::~HuhiExtensionsAPIProvider() = default;

void HuhiExtensionsAPIProvider::AddAPIFeatures(FeatureProvider* provider) {
  AddHuhiAPIFeatures(provider);
}

void HuhiExtensionsAPIProvider::AddManifestFeatures(
    FeatureProvider* provider) {
  AddHuhiManifestFeatures(provider);
}

void HuhiExtensionsAPIProvider::AddPermissionFeatures(
    FeatureProvider* provider) {
  AddHuhiPermissionFeatures(provider);
}

void HuhiExtensionsAPIProvider::AddBehaviorFeatures(
    FeatureProvider* provider) {
  // No huhi-specific behavior features.
}

void HuhiExtensionsAPIProvider::AddAPIJSONSources(
    JSONFeatureProviderSource* json_source) {
  json_source->LoadJSON(IDR_HUHI_EXTENSION_API_FEATURES);
}

bool HuhiExtensionsAPIProvider::IsAPISchemaGenerated(
    const std::string& name) {
  return api::HuhiGeneratedSchemas::IsGenerated(name);
}

base::StringPiece HuhiExtensionsAPIProvider::GetAPISchema(
    const std::string& name) {
  return api::HuhiGeneratedSchemas::Get(name);
}

void HuhiExtensionsAPIProvider::RegisterPermissions(
    PermissionsInfo* permissions_info) {
  // No huhi-specific permissions.
}

void HuhiExtensionsAPIProvider::RegisterManifestHandlers() {
  // No huhi-specific manifest handlers.
}

}  // namespace extensions
