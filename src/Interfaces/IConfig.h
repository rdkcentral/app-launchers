#pragma once
#include <string>

class IConfig {
public:
    virtual ~IConfig() = default;
    virtual bool Parse() = 0;
    virtual bool Contains(const std::string& key) const = 0;

    // WIP - no std::variant :(
    virtual std::string GetString(const std::string& key) = 0;
    virtual double GetNumber(const std::string& key) = 0;
    virtual bool GetBoolean(const std::string& key) = 0;
};