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

#include "IConfig.h"
#include "JsonConfig.h"
#include "LauncherFactory.h"
#include <algorithm>
#include <iostream>
#include <string>

#ifdef MOCK_LIFECYCLE
#include "LifeCycleCLI.h"
#endif

int main(int argc, char** argv)
{

    std::string launcherType = "COBALT";
    if (argc > 1) {
        launcherType = std::string(argv[1]);
        std::transform(launcherType.begin(), launcherType.end(), launcherType.begin(), ::toupper);
    }
#ifdef MOCK_LIFECYCLE
    std::unique_ptr<ILifeCycle> lifecycle(new LifeCycleCLI());
#else
    std::unique_ptr<ILifeCycle> lifecycle(nullptr);
#endif

    int result = -1;
    auto launcher = LauncherFactory::Create(launcherType, lifecycle.get());
    if (!launcher) {
        std::cerr << "Launcher for: " << launcherType << " not found.\n";
        return result;
    }

    std::string configPath = "/etc/launcher_config.json";
    std::unique_ptr<IConfig> config(new JsonConfig(configPath));
    if (!config->Parse()) {
        std::cerr << "Unable to parse configuration from " << configPath << "\n";
        return result;
    }

    if (!launcher->Configure(config.get())) {
        std::cerr << "Unable to configure launcher with given configuration.\n";
        return result;
    }

#ifdef MOCK_LIFECYCLE
    lifecycle->Start();
#endif
    result = launcher->Run();
    std::cout << "Launcher exited with: " << result << std::endl;

    return result;
}
