/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <functional>
#include <stdint.h>
#include <unordered_map>
#include <mutex>

class ILifeCycle {

public:
    enum StateChange : uint8_t { SUSPEND, RESUME, PAUSE, UNPAUSE, QUIT };
    using Callback = std::function<void(void)>;
    using CallbackMap = std::unordered_map<StateChange, Callback>;

    virtual ~ILifeCycle() = default;

    virtual void Register(StateChange state, const Callback& callback)
    {
        std::lock_guard<std::mutex> guard(m_callbacksMutex);
        m_callbacks.insert({ state, callback });
    }
    virtual void Unregister(StateChange state)
    {
        std::lock_guard<std::mutex> guard(m_callbacksMutex);
        m_callbacks.erase(state);
    }

    virtual void Start() = 0;
    virtual void Stop() = 0;

protected:
    std::mutex m_callbacksMutex;
    CallbackMap m_callbacks;
};
