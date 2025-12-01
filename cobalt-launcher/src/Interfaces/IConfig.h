/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <string>
#include <utility>

class IConfig {
public:
    virtual ~IConfig() = default;
    virtual bool Parse() = 0;
    virtual bool Contains(const std::string& key) const = 0;

    // WIP - no std::variant :(
    virtual std::pair<bool, std::string> GetString(const std::string& key) const = 0;
    virtual std::pair<bool, double> GetNumber(const std::string& key) const = 0;
    virtual std::pair<bool, bool> GetBoolean(const std::string& key) const = 0;
};
