#pragma once
#include <IConfig.h>
#include <string>
#include <unordered_map>

class CobaltConfig : public IConfig {
public:
    explicit CobaltConfig(std::string path);
    ~CobaltConfig() override = default;

    bool Parse() override;
    const ConfigurationMap& GetConfiguration() const override;

private:
    std::string m_path;
    ConfigurationMap m_configuration;

};
