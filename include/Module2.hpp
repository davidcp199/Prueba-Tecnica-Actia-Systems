#pragma once
#include "IModule.hpp"
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>

class Module2 : public IModule {
public:
    Module2();
    ~Module2();

    void start() override;
    void stop() override;
    void deliver(const std::vector<unsigned char>& data) override;
    void setNextModule(IModule* next) override;

private:
    void run();
    std::thread worker;
    std::atomic<bool> running;

    IModule* nextModule;
    std::queue<std::vector<unsigned char>> buffer;
    std::mutex buffer_mutex;
};
