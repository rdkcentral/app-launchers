#pragma once
#include <functional>
#include <stdint.h>

class ILifeCycle {

public:
    enum StateChange : uint8_t { SUSPEND, RESUME, PAUSE, UNPAUSE, QUIT };
    using Callback = std::function<void(void)>;
    using CallbackMap = std::unordered_map<StateChange, Callback>;

    virtual ~ILifeCycle() = default;

    virtual void Register(StateChange state, const Callback& callback)
    {
        m_callbacks.insert({ state, callback });
    }
    virtual void Unregister(StateChange state)
    {
        m_callbacks.erase(state);
    }

    virtual void Start() = 0;
    virtual void Stop() = 0;

protected:
    CallbackMap m_callbacks;
};