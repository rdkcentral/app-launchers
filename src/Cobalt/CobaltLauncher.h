#pragma once
#include "ILauncher.h"
#include <atomic>
#include <thread>

class CobaltLauncher : public ILauncher {
public:
    CobaltLauncher() = default;
    ~CobaltLauncher() override = default;
    int Run() override;
    bool Configure(std::unique_ptr<IConfig> config) override;

private:
    int Worker();
    std::unique_ptr<IConfig> m_config;
    std::thread m_worker;
    std::atomic_bool m_isRunning{ false };
};
