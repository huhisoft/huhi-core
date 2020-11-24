/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_BINANCE_BROWSER_BINANCE_JSON_PARSER_H_
#define HUHI_COMPONENTS_BINANCE_BROWSER_BINANCE_JSON_PARSER_H_

#include <map>
#include <string>
#include <vector>

class BinanceJSONParser {
 public:
  static bool GetTokensFromJSON(const std::string& json,
                                std::string *value, std::string type);
  static bool GetAccountBalancesFromJSON(const std::string& json,
      std::map<std::string, std::vector<std::string>>* balances);
  static bool GetQuoteIDFromJSON(const std::string& json,
                                 std::string *quote_id);
  static bool GetDepositInfoFromJSON(const std::string& json,
                                     std::string* address,
                                     std::string* tag);
  static bool GetQuoteInfoFromJSON(const std::string& json,
                                   std::string* quote_id,
                                   std::string* quote_price,
                                   std::string* total_fee,
                                   std::string* total_amount);
  static bool GetConfirmStatusFromJSON(const std::string& json,
                                       std::string *error_message,
                                       bool* success_status);
  static bool GetConvertAssetsFromJSON(const std::string& json,
      std::map<std::string, std::vector<std::string>>* assets);
  static bool RevokeTokenFromJSON(const std::string& json,
                                  bool* success_status);
  static bool GetCoinNetworksFromJSON(const std::string& json,
      std::map<std::string, std::string>* networks);
};

#endif  // HUHI_COMPONENTS_BINANCE_BROWSER_BINANCE_JSON_PARSER_H_
