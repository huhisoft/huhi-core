/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_PERF_PREDICTOR_BROWSER_BANDWIDTH_LINREG_H_
#define HUHI_COMPONENTS_HUHI_PERF_PREDICTOR_BROWSER_BANDWIDTH_LINREG_H_

#include <string>
#include <vector>

#include "base/containers/flat_map.h"
#include "huhi/components/huhi_perf_predictor/browser/bandwidth_linreg_parameters.h"

namespace huhi_perf_predictor {

constexpr double kOutlierThreshold = 6;
// if above 20MB _and_ more than 6x of the transfer size, probably an outlier
constexpr double kSavingsAbsoluteOutlier = 20 << 20;

// Computes prediction based on the provided feature vector.
// It is the client's responsibility to provide features in
// the exact order expected by the predictor.
double LinregPredictVector(const std::array<double, feature_count>& features);

// Computes prediction based on key-value map of features.
// It translates the map to a feature vector internally, and
// it is the client's responsibility to ensure that all required
// features are present and only the necessary features are provided.
// The function uses 0 for any features not provided and ignores
// any extra features.
double LinregPredictNamed(const base::flat_map<std::string, double>& features);

}  // namespace huhi_perf_predictor

#endif  // HUHI_COMPONENTS_HUHI_PERF_PREDICTOR_BROWSER_BANDWIDTH_LINREG_H_
