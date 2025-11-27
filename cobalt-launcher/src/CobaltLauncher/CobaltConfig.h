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

#include "IConfig.h"
#include <string>
#include <utility>

class CobaltConfig {
public:
    CobaltConfig() = default;
    ~CobaltConfig() = default;

    bool Configure(IConfig* config)
    {
        if (config) {
            m_config = config;
            return true;
        }
        return false;
    }

    std::pair<bool, std::string> GetUrl()
    {
        if (m_config) {
            if (m_config->Contains("configuration.url")) {
                return { true, m_config->GetString("configuration.url") };
            }
            return { false, "" };
        }

        return { false, "" };
    }
    // TODO: implement, reducing boilerplate
    std::pair<bool, std::string> GetClientIdentifier()
    {
        if (m_config) {
            if (m_config->Contains("configuration.clientidentifier")) {
                return { true, m_config->GetString("configuration.clientidentifier") };
            }
            return { false, "" };
        }

        return { false, "" };
    }
    std::pair<bool, std::string> GetLanguage()
    {
        if (m_config) {
            if (m_config->Contains("configuration.language")) {
                return { true, m_config->GetString("configuration.language") };
            }
            return { false, "" };
        }

        return { false, "" };
    }
    std::pair<bool, std::string> GetContentDir()
    {
        if (m_config) {
            if (m_config->Contains("configuration.contentdir")) {
                return { true, m_config->GetString("configuration.contentdir") };
            }
            return { false, "" };
        }

        return { false, "" };
    }
    std::pair<bool, std::string> GetGstDebug()
    {
        if (m_config) {
            if (m_config->Contains("configuration.gstdebug")) {
                return { true, m_config->GetString("configuration.gstdebug") };
            }
            return { false, "" };
        }

        return { false, "" };
    }
    std::pair<bool, std::string> GetEssosContextDestroy()
    {
        if (m_config) {
            if (m_config->Contains("configuration.essoscontextdestroy")) {
                return { true, m_config->GetString("configuration.essoscontextdestroy") };
            }
            return { false, "" };
        }

        return { false, "" };
    }
    std::pair<bool, bool> GetPreloadEnabled()
    {
        if (m_config) {
            if (m_config->Contains("configuration.preload")) {
                return { true, m_config->GetBoolean("configuration.preload") };
            }
            return { false, false };
        }

        return { false, false };
    }
    std::pair<bool, uint16_t> GetAutoSuspendDelay()
    {
        if (m_config) {
            if (m_config->Contains("configuration.autosuspenddelay")) {
                return { true, m_config->GetNumber("configuration.autosuspenddelay") };
            }
            return { false, 0 };
        }

        return { false, 0 };
    }
    std::pair<bool, std::string> GetClosurePolicy()
    {
        if (m_config) {
            if (m_config->Contains("configuration.closurepolicy")) {
                return { true, m_config->GetString("configuration.closurepolicy") };
            }
            return { false, "" };
        }

        return { false, "" };
    }
    std::pair<bool, std::string> GetFireboltEndpoint()
    {
        if (m_config) {
            if (m_config->Contains("configuration.fireboltendpoint")) {
                return { true, m_config->GetString("configuration.fireboltendpoint") };
            }
            return { false, "" };
        }

        return { false, "" };
    }

    // FIXME: Get all the fields as JSON string
    std::pair<bool, std::string> GetSystemProperties()
    {
        if (m_config) {
            if (m_config->Contains("configuration.systemproperties")) {
                return { true, m_config->GetString("configuration.systemproperties") };
            }
            return { false, "" };
        }

        return { false, "" };
    }

    // FIXME: Get all the fields as JSON string
    std::pair<bool, std::string> GetAdvertisingId()
    {
        if (m_config) {
            if (m_config->Contains("configuration.advertisingid")) {
                return { true, m_config->GetString("configuration.advertisingid") };
            }
            return { false, "" };
        }

        return { false, "" };
    }
    // TODO: SbMainArgs
private:
    IConfig* m_config;
};
