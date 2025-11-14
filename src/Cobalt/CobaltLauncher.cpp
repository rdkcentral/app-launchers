#include "CobaltLauncher.h"
#include <iostream>

#include <chrono>

int CobaltLauncher::Run()
{
    std::cout << "Cobalt starting...\n";
    m_isRunning = true;
    m_worker = std::thread(&CobaltLauncher::Worker, this);
    return 1;
}

bool CobaltLauncher::Configure(std::unique_ptr<IConfig> config)
{
    std::cout << "Cobalt configuring...\n";
    m_config = std::move(config);
    return m_config.get() != nullptr;
}

int CobaltLauncher::Worker()
{
    while (m_isRunning) {
        std::cout << "RUNNING\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}