#include "LifeCycleCLI.h"
#include <iostream>

LifeCycleCLI::~LifeCycleCLI()
{
    Stop();
}

void LifeCycleCLI::Start()
{
    m_isRunning = true;
    m_worker = std::thread(&LifeCycleCLI::Worker, this);
}
void LifeCycleCLI::Stop()
{
    m_isRunning = false;
    if (m_worker.joinable()) {
        m_worker.join();
    }
}
void LifeCycleCLI::Worker()
{
    std::string option;
    while (m_isRunning) {
        std::cout << "Pass option\n";
        std::cin >> option;
        if (option == "quit") {
            m_callbacks.at(QUIT)();
        }
    }
}