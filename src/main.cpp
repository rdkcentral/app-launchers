#include "IConfig.h"
#include "JsonConfig.h"
#include "LauncherFactory.h"
#include "LifeCycleCLI.h"
#include <algorithm>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{

    std::string launcherType = "COBALT";
    if (argc > 1) {
        launcherType = std::string(argv[1]);
        std::transform(launcherType.begin(), launcherType.end(), launcherType.begin(), ::toupper);
    }
    std::string configPath = "/tmp/config.json";

    std::unique_ptr<ILifeCycle> lifecycle(new LifeCycleCLI());

    auto launcher = LauncherFactory::Create(launcherType, lifecycle.get());

    // WIP
    std::unique_ptr<IConfig> config(new JsonConfig(configPath));
    config->Parse();

    auto isConfigured = launcher->Configure(config.get());

    lifecycle->Start();

    int result = -1;
    if (isConfigured) {
        result = launcher->Run();
    }

    lifecycle->Stop();
    std::cout << "Launcher exited with: " << result << std::endl;

    return 0;
}