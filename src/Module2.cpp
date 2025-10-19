#include "Module2.hpp"
#include <algorithm>
#include <chrono>
#include <thread>

Module2::Module2() : running(false), nextModule(nullptr) {}

Module2::~Module2() { stop(); }

void Module2::setNextModule(IModule* next) {
    nextModule = next;
}

void Module2::start() {
    running = true;
    worker = std::thread(&Module2::run, this);
}

void Module2::stop() {
    running = false;
    if(worker.joinable()) worker.join();
}

void Module2::deliver(const std::vector<unsigned char>& data) {
    std::lock_guard<std::mutex> lock(buffer_mutex);
    if(buffer.size() < 100) buffer.push(data);
}

void Module2::run() {
    std::vector<unsigned char> pattern = {0x00, 0xFF};

    while(running) {
        std::vector<unsigned char> data;
        {
            std::lock_guard<std::mutex> lock(buffer_mutex);
            if(!buffer.empty()) {
                data = buffer.front();
                buffer.pop();
            }
        }

        if(!data.empty()) {
            auto it = std::search(data.begin(), data.end(), pattern.begin(), pattern.end());
            if(it != data.end() && nextModule) {
                nextModule->deliver(data);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
