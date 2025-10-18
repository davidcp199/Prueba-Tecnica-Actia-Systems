#pragma once
#include "IModule.hpp"
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
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

private:
    void run(); // Hilo interno
    std::thread worker;
    std::atomic<bool> running;

    std::queue<std::pair<std::chrono::system_clock::time_point, std::vector<unsigned char>>> buffer;
    std::mutex buffer_mutex;

    // Almacena todos los arrays recibidos para imprimir
    std::vector<std::pair<std::chrono::system_clock::time_point, std::vector<unsigned char>>> all_records;
};
