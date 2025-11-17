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
    std::pair<bool, std::string> GetClientIdentifier();
    std::pair<bool, std::string> GetLanguage();
    std::pair<bool, std::string> GetContentDir();
    std::pair<bool, std::string> GetGstDebug();
    std::pair<bool, std::string> GetEssosContextDestroy();
    std::pair<bool, bool> GetPreloadEnabled();
    std::pair<bool, uint16_t> GetAutoSuspendDelay();
    std::pair<bool, std::string> GetClosurePolicy();
    std::pair<bool, std::string> GetFireboltEndpoint();

    std::pair<bool, std::string> GetSystemProperties();
    std::pair<bool, std::string> GetAdvertisingId();
    // TODO: SbMainArgs
private:
    IConfig* m_config;
};