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

#include "LifeCycleCLI.h"
#include <iostream>
#include <mutex>

LifeCycleCLI::~LifeCycleCLI()
{
    Stop();
}

/**
 * @brief MOCK
 */
void LifeCycleCLI::Start()
{
    m_isRunning = true;
    m_worker = std::thread(&LifeCycleCLI::Worker, this);
}

/**
 * @brief MOCK
 */
void LifeCycleCLI::Stop()
{
    m_isRunning = false;
    if (m_worker.joinable()) {
        m_worker.join();
    }
}
/**
 * @brief MOCK
 */
void LifeCycleCLI::Worker()
{
    std::string option;
    while (m_isRunning) {
        std::cout << "Pass option\n";
        std::cin >> option;
        if (option == "quit") {
            std::lock_guard<std::mutex> guard(m_callbacksMutex);
            auto callback = m_callbacks.find(QUIT);
            if (callback != m_callbacks.end() && callback->second) {
                callback->second();
            }
        }
    }
}
