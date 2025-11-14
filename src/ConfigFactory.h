#include "CobaltConfig.h"
#include <memory>
#include <string>

class ConfigFactory {
public:
    static std::unique_ptr<IConfig> Create(const std::string& type, const std::string& path)
    {
        if (type == "COBALT") {
            return std::make_unique<CobaltConfig>(path);
        }

        return nullptr;
    }
};