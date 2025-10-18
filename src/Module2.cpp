#include "Module2.hpp"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

Module2::Module2()
    : running(false), nextModule(NULL)
{
}

Module2::~Module2() {
    stop();
}

void Module2::start() {
    running = true;
    worker = std::thread(&Module2::run, this);
}

void Module2::stop() {
    running = false;
    if (worker.joinable())
        worker.join();
}

void Module2::setNextModule(IModule* next) {
    nextModule = next;
}

void Module2::deliver(const std::vector<unsigned char>& data) {
    std::lock_guard<std::mutex> lock(bufferMutex);
    if (buffer.size() < 100)
        buffer.push(data);
}

void Module2::run() {
    std::vector<unsigned char> pattern;
    pattern.push_back(0x00);
    pattern.push_back(0x01);
    pattern.push_back(0x02);

    while (running) {
        std::vector<unsigned char> data;
        bool hasData = false;

        // Sacar un elemento del buffer
        {
            std::lock_guard<std::mutex> lock(bufferMutex);
            if (!buffer.empty()) {
                data = buffer.front();
                buffer.pop();
                hasData = true;
            }
        }

        if (hasData) {
            std::vector<unsigned char>::iterator it;
            it = std::search(data.begin(), data.end(), pattern.begin(), pattern.end());

            if (it != data.end()) {
                std::cout << "Module2: secuencia encontrada, enviando al siguiente modulo.\n";
                if (nextModule != NULL)
                    nextModule->deliver(data);
            } else {
                std::cout << "Module2: secuencia no encontrada, descartando.\n";
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
