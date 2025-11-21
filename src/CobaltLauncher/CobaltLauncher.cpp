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
}

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
        std::cout << "Launchung with url: " << url.second << "\n";
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

    auto language = m_config.GetLanguage();
    if (language.first) {
        SetEnvironment("LANG", language.second);
    }

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

    return true;
}

void CobaltLauncher::Quit()
{
    std::cout << "QUIT\n";
    m_isRunning = false;
    SbRdkQuit();
}