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

#include "CobaltLauncher.h"
#include <memory>
#include <string>

class LauncherFactory {
public:
    static std::unique_ptr<ILauncher> Create(const std::string& type, ILifeCycle* lifecycle)
    {
        if (type == "COBALT") {
            return std::unique_ptr<CobaltLauncher>(new CobaltLauncher(lifecycle));
        }
        return nullptr;
    }
};