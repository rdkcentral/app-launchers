#include "ConfigFactory.h"
#include "LauncherFactory.h"
#include <algorithm>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{

    std::string launcherType = "COBALT";
    if (argc > 1) {
        launcherType = std::string(argv[1]);
        std::ranges::transform(launcherType, launcherType.begin(), ::toupper);
    }
    std::string configPath = "/tmp/config.json";

    auto launcher = LauncherFactory::Create(launcherType);
    auto config = ConfigFactory::Create(launcherType, configPath);
    config->Parse();

    auto isConfigured = launcher->Configure(std::move(config));

    int result = -1;
    if (isConfigured) {
        result = launcher->Run();
    }

    std::cout << "Launcher exited with: " << result << std::endl;

    return 0;
}