#pragma once
#include "CobaltConfig.h"
#include "ILauncher.h"
#include "ILifeCycle.h"
#include <atomic>

class CobaltLauncher : public ILauncher {
public:
    static const char DEFAULT_CONTENT_DIR[];
    static const std::string CLIENT_IDENTIFIER;

    explicit CobaltLauncher(ILifeCycle* lifecycle);
    ~CobaltLauncher() override = default;
    int Run() override;
    bool Configure(IConfig* config) override;

private:
    void Quit();

    CobaltConfig m_config;
    ILifeCycle* m_lifecycle{ nullptr };

    std::atomic_bool m_isRunning{ true };
};
