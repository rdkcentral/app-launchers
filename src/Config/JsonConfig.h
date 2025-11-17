#pragma once
#include "IConfig.h"
#include <memory>
#include <string>

class JsonConfig : public IConfig {
public:
    explicit JsonConfig(std::string filename);
    ~JsonConfig() override;

    bool Parse() override;
    bool Contains(const std::string& key) const override;

    std::string GetString(const std::string& key) override;
    double GetNumber(const std::string& key) override;
    bool GetBoolean(const std::string& key) override;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};