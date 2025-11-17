#include "CobaltLauncher.h"
#include <iostream>

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

    auto result = m_config.GetUrl();
    if (result.first) {
        std::cerr << "Launchung with url: " << result.second << "\n";
    } else {
        std::cerr << "Launchung without url \n";
    }

    // simulate blocking call to SbRdkMain
    while (m_isRunning) {
    }
    return 1;
}

bool CobaltLauncher::Configure(IConfig* config)
{
    std::cout << "Cobalt configuring...\n";
    return m_config.Configure(config);
}

void CobaltLauncher::Quit()
{
    m_isRunning = false;
    std::cout << "QUIT\n";
}