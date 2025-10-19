#pragma once
#include "IModule.hpp"
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>

class Module3 : public IModule {
public:
    Module3();
    ~Module3();

    void start() override;
    void stop() override;
    void deliver(const std::vector<unsigned char>& data) override;
    void setNextModule(IModule* next) override;

private:
    struct Record {
        std::vector<unsigned char> data;
        std::chrono::system_clock::time_point timestamp;
    };

    void run();

    std::thread worker;
    std::atomic<bool> running;

    std::queue<Record> buffer;    // Buffer de entrada
    std::mutex buffer_mutex;

    std::vector<Record> records;  // Todos los registros guardados
    const size_t maxBuffer = 100;
};
