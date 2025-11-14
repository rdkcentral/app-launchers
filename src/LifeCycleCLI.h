#pragma once
#include "Interfaces/ILifeCycle.h"
#include <functional>
#include <stdint.h>
#include <thread>

class LifeCycleCLI : public ILifeCycle {
public:
    using CallbackMap = std::unordered_map<StateChange, Callback>;

    LifeCycleCLI() = default;
    ~LifeCycleCLI() override;

    void Start() override;
    void Stop() override;

private:
    void Worker();
    std::atomic_bool m_isRunning{ false };
    std::thread m_worker;
};