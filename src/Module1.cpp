#include "Module1.hpp"
#include <chrono>
#include <iostream>

Module1::Module1()
    : running(false), nextModule(nullptr)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

Module1::~Module1() {
    stop();
}

void Module1::start() {
    running = true;
    worker = std::thread(&Module1::run, this);
}

void Module1::stop() {
    running = false;
    if (worker.joinable())
        worker.join();
}

void Module1::deliver(const std::vector<unsigned char>&) {
    // Este módulo no recibe datos, solo los genera
}

void Module1::setNextModule(IModule* next) {
    nextModule = next;
}

void Module1::run() {
    while (running) {
        int size = 1 + std::rand() % 100;
        std::vector<unsigned char> data(size);

        for (int i = 0; i < size; ++i)
            data[i] = static_cast<unsigned char>(std::rand() % 256);

        if (nextModule)
            nextModule->deliver(data);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
