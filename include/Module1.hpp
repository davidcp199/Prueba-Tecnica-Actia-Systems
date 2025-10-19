#pragma once
#include "IModule.hpp"
#include <thread>
#include <vector>
#include <atomic>

class Module1 : public IModule {
public:
    Module1();
    ~Module1();

    void start() override;
    void stop() override;
    void deliver(const std::vector<unsigned char>& data) override;
    void setNextModule(IModule* next) override;

private:
    void run();

    std::thread worker;
    std::atomic<bool> running;
    IModule* nextModule;
};
