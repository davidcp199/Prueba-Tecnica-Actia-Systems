#pragma once
#include "IModule.hpp"
#include <vector>
#include <mutex>
#include <iostream>
#include <chrono>

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

    std::vector<Record> records; // Buffer de hasta 100 arrays
    std::mutex mtx;
    const size_t maxBuffer = 100;
};
