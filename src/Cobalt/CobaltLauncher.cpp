#include "CobaltLauncher.h"
#include <iostream>

#include <chrono>

CobaltLauncher::CobaltLauncher(ILifeCycle* lifecycle)
    : m_lifecycle(lifecycle)
{
    if (m_lifecycle) {
        m_lifecycle->Register(ILifeCycle::QUIT, std::bind(&CobaltLauncher::Quit, this));
    }
}

int CobaltLauncher::Run()
{
    std::cout << "Cobalt starting...\n";
    while (m_isRunning) {
    }
    return 1;
}

bool CobaltLauncher::Configure(std::unique_ptr<IConfig> config)
{
    std::cout << "Cobalt configuring...\n";
    m_config = std::move(config);
    return m_config.get() != nullptr;
}

void CobaltLauncher::Quit()
{
    m_isRunning = false;
    std::cout << "QUIT\n";
}