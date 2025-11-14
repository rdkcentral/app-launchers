#pragma once

#include "CobaltLauncher.h"
#include <memory>
#include <string>

class LauncherFactory {
public:
    static std::unique_ptr<ILauncher> Create(const std::string& type)
    {
        if (type == "COBALT") {
            return std::make_unique<CobaltLauncher>();
        }
        return nullptr;
    }
};