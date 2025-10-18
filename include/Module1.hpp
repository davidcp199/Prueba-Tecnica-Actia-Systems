#ifndef MODULE1_H
#define MODULE1_H

#include "IModule.hpp"
#include <thread>
#include <vector>
#include <atomic>
#include <cstdlib>
#include <ctime>

class Module1 : public IModule {
public:
    Module1();
    ~Module1();

    void start() override;
    void stop() override;
    void deliver(const std::vector<unsigned char>& data) override;

    // Permite definir el siguiente módulo receptor
    void setNextModule(IModule* next);

private:
    void run(); // hilo principal de generación

    std::thread worker;
    std::atomic<bool> running;
    IModule* nextModule;
};

#endif // MODULE1_H
