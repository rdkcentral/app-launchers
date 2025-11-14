#pragma once
#include <unordered_map>

class IConfig {
public:
    using ConfigurationMap = std::unordered_map<std::string, std::string>;

    virtual ~IConfig() = default;
    virtual bool Parse() = 0;
    virtual const ConfigurationMap& GetConfiguration() const = 0;
};
