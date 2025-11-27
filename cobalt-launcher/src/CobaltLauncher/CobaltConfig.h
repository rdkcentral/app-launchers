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
            m_config->GetString("configuration.url");
        }

        return { false, "" };
    }
    std::pair<bool, std::string> GetClientIdentifier()
    {
        if (m_config) {
            return m_config->GetString("configuration.clientidentifier");
        }

        return { false, "" };
    }
    std::pair<bool, std::string> GetLanguage()
    {
        if (m_config) {
            return m_config->GetString("configuration.language");
        }

        return { false, "" };
    }
    std::pair<bool, std::string> GetContentDir()
    {
        if (m_config) {
            m_config->GetString("configuration.contentdir");
        }

        return { false, "" };
    }
    std::pair<bool, std::string> GetGstDebug()
    {
        if (m_config) {
            m_config->GetString("configuration.gstdebug");
        }

        return { false, "" };
    }
    std::pair<bool, std::string> GetEssosContextDestroy()
    {
        if (m_config) {
            m_config->GetString("configuration.essoscontextdestroy");
        }

        return { false, "" };
    }
    std::pair<bool, bool> GetPreloadEnabled()
    {
        if (m_config) {
            m_config->GetBoolean("configuration.preload");
        }

        return { false, false };
    }
    std::pair<bool, uint16_t> GetAutoSuspendDelay()
    {
        if (m_config) {
            m_config->GetNumber("configuration.autosuspenddelay");
        }

        return { false, 0 };
    }
    std::pair<bool, std::string> GetClosurePolicy()
    {
        if (m_config) {
            m_config->GetString("configuration.closurepolicy");
        }

        return { false, "" };
    }
    std::pair<bool, std::string> GetFireboltEndpoint()
    {
        if (m_config) {
            return m_config->GetString("configuration.fireboltendpoint");
        }

        return { false, "" };
    }

    std::pair<bool, std::string> GetSystemProperties()
    {
        if (m_config) {
            m_config->GetString("configuration.systemproperties");
        }

        return { false, "" };
    }

    std::pair<bool, std::string> GetAdvertisingId()
    {
        if (m_config) {
            m_config->GetString("configuration.advertisingid");
        }

        return { false, "" };
    }
    // TODO: SbMainArgs
private:
    IConfig* m_config{ nullptr };
};
