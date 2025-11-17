#pragma once
#include "IConfig.h"

class ILauncher {
public:
    virtual ~ILauncher() = default;
    virtual int Run() = 0;
    virtual bool Configure(IConfig* config) = 0;
};
