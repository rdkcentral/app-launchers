#pragma once
#include "ILifeCycle.h"
#include <thread>
#include <atomic>

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