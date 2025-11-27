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

#include "CobaltLauncher.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

#ifdef MOCK_SB
extern "C" {

int StarboardMain(int argc, char** argv)
{
    return 0;
}
void SbRdkHandleDeepLink(const char* link)
{
}
void SbRdkSuspend()
{
}
void SbRdkResume()
{
}
void SbRdkPause()
{
}
void SbRdkUnpause()
{
}
void SbRdkQuit()
{
}
void SbRdkSetSetting(const char* key, const char* json)
{
}
int SbRdkGetSetting(const char* key, char** out_json)
{
    return 0;
}

typedef int (*SbRdkCallbackFunc)(void* user_data);
void SbRdkSetConcealRequestHandler(SbRdkCallbackFunc cb, void* user_data)
{
}
void SbRdkSetCobaltExitStrategy(const char* strategy)
{
}

} // extern "C"
#else
extern "C" {

int StarboardMain(int argc, char** argv);
void SbRdkHandleDeepLink(const char* link);
void SbRdkSuspend();
void SbRdkResume();
void SbRdkPause();
void SbRdkUnpause();
void SbRdkQuit();
void SbRdkSetSetting(const char* key, const char* json);
int SbRdkGetSetting(const char* key, char** out_json);

typedef int (*SbRdkCallbackFunc)(void* user_data);
void SbRdkSetConcealRequestHandler(SbRdkCallbackFunc cb, void* user_data);
void SbRdkSetCobaltExitStrategy(const char* strategy);

} // extern "C"
#endif

namespace {
void SetEnvironment(const std::string& key, const std::string& value, bool forced = false)
{
    ::setenv(key.c_str(), value.c_str(), forced);
}
bool GetEnvironment(const std::string& key, std::string& value)
{
    const char* envVal = std::getenv(key.c_str());
    if (envVal != nullptr) {
        value = envVal;
        return true;
    } else {
        value.clear();
        return false;
    }
}
}

const char CobaltLauncher::DEFAULT_CONTENT_DIR[] = "/usr/share/content/data:"
                                                   "/media/apps/libcobalt/usr/share/content/data:"
                                                   "/tmp/libcobalt/usr/share/content/data";
const std::string CobaltLauncher::CLIENT_IDENTIFIER = "CobaltLauncher";

CobaltLauncher::CobaltLauncher(ILifeCycle* lifecycle)
    : m_lifecycle(lifecycle)
{
    if (m_lifecycle) {
        m_lifecycle->Register(ILifeCycle::QUIT, std::bind(&CobaltLauncher::Quit, this));
    }
}

int CobaltLauncher::Run()
{
    std::cout << "Cobalt starting...\n";
    std::vector<const char*> argv;
    argv.push_back("Cobalt");

    auto url = m_config.GetUrl();
    if (url.first) {
        std::cout << "Launching with url: " << url.second << "\n";
        argv.push_back(url.second.c_str());
    }

    auto preload = m_config.GetPreloadEnabled();
    if (preload.first && preload.second) {
        argv.push_back("--preload");
    }

    int result = -1;
    while (m_isRunning) {
        result = StarboardMain(argv.size(), const_cast<char**>(argv.data()));
    }
    return result;
}

bool CobaltLauncher::Configure(IConfig* config)
{
    std::cout << "Cobalt configuring...\n";

    if (!m_config.Configure(config)) {
        return false;
    }
    // TODO:
    // HOME - persistent path,
    // COBALT_TEMP - volatile path,

    auto clientIdentifier = m_config.GetClientIdentifier();
    if (clientIdentifier.first) {
        std::string value = CobaltLauncher::CLIENT_IDENTIFIER + "," + clientIdentifier.second;
        SetEnvironment("CLIENT_IDENTIFIER", value);
        SetEnvironment("WAYLAND_DISPLAY", clientIdentifier.second);
    } else {
        SetEnvironment("CLIENT_IDENTIFIER", CobaltLauncher::CLIENT_IDENTIFIER);
    }

    auto language = m_config.GetLanguage();
    if (language.first) {
        SetEnvironment("LANG", language.second);
    }

    auto contentDir = m_config.GetContentDir();
    if (contentDir.first) {
        SetEnvironment("COBALT_CONTENT_DIR", contentDir.second);
    } else {
        SetEnvironment("COBALT_CONTENT_DIR", CobaltLauncher::DEFAULT_CONTENT_DIR);
    }

    std::string envVal, gstDebug = "gstplayer:4,2";
    if (GetEnvironment("GST_DEBUG", envVal) && !envVal.empty()) {
        gstDebug = envVal;
    }
    auto gstDebugConfig = m_config.GetGstDebug();
    if (gstDebugConfig.first) {
        gstDebug += "," + gstDebugConfig.second;
    }
    SetEnvironment("GST_DEBUG", gstDebug);

    auto essosContextDestroy = m_config.GetEssosContextDestroy();
    if (essosContextDestroy.first) {
        SetEnvironment("COBALT_ESSOS_CONTEXT_DESTROY", essosContextDestroy.second);
    }

    auto autoSuspendDelay = m_config.GetAutoSuspendDelay();
    if (autoSuspendDelay.first) {
        // TODO: Schedule auto suspend;
    }

    auto systemProperties = m_config.GetSystemProperties();
    if (systemProperties.first) {
        SbRdkSetSetting("systemproperties", systemProperties.second.c_str());
    }

    auto advertisingId = m_config.GetAdvertisingId();
    if (advertisingId.first) {
        SbRdkSetSetting("advertisingId", advertisingId.second.c_str());
    }

    auto fireboltEndpoint = m_config.GetFireboltEndpoint();
    if (fireboltEndpoint.first) {
        SetEnvironment("FIREBOLT_ENDPOINT", fireboltEndpoint.second);
    }

    auto closurePolicy = m_config.GetClosurePolicy();
    if (closurePolicy.first) {
        SbRdkSetCobaltExitStrategy(closurePolicy.second.c_str());
    }
    // TODO:
    // SbRdkSetConcealRequestHandler - request suspend

    return true;
}

void CobaltLauncher::Quit()
{
    std::cout << "QUIT\n";
    m_isRunning = false;
    SbRdkQuit();
}
