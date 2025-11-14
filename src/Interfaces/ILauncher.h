#pragma once
#include "IConfig.h"

class ILauncher {
public:
    virtual ~ILauncher() = default;
    virtual int Run() = 0;
    virtual bool Configure(std::unique_ptr<IConfig> config) = 0;
};
