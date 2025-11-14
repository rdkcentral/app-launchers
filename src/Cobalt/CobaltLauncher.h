#pragma once
#include "ILauncher.h"
#include "ILifeCycle.h"
#include <atomic>

class CobaltLauncher : public ILauncher {
public:
    explicit CobaltLauncher(ILifeCycle* lifecycle);
    ~CobaltLauncher() override = default;
    int Run() override;
    bool Configure(std::unique_ptr<IConfig> config) override;

private:
    void Quit();

    std::unique_ptr<IConfig> m_config;
    ILifeCycle* m_lifecycle{ nullptr };

    std::atomic_bool m_isRunning{ true };
};
