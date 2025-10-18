#include "Module3.hpp"
#include <algorithm>

Module3::Module3() : running(false) {}

Module3::~Module3() {
    stop();
}

void Module3::start() {
    running = true;
    worker = std::thread(&Module3::run, this);
}

void Module3::stop() {
    running = false;
    if(worker.joinable())
        worker.join();
}

void Module3::deliver(const std::vector<unsigned char>& data) {
    std::lock_guard<std::mutex> lock(buffer_mutex);
    if(buffer.size() < 100) {
        buffer.push({std::chrono::system_clock::now(), data});
    }
}

void Module3::run() {
    while(running) {
        std::pair<std::chrono::system_clock::time_point, std::vector<unsigned char>> item;

        {
            std::lock_guard<std::mutex> lock(buffer_mutex);
            if(!buffer.empty()) {
                item = buffer.front();
                buffer.pop();
                all_records.push_back(item);
            } else {
                item.second.clear();
            }
        }

        if(!item.second.empty()) {
            std::sort(all_records.begin(), all_records.end(),
                [](const auto& a, const auto& b){
                    return a.first < b.first;
                });

            std::cout << "----- Array Total de Coincidencias -----\n";
            for(const auto& rec : all_records) {
                std::time_t t = std::chrono::system_clock::to_time_t(rec.first);
                std::cout << "[" << std::ctime(&t) << "] ";
                for(unsigned char b : rec.second)
                    std::cout << std::hex << (int)b << " ";
                std::cout << std::dec << "\n";
            }
            std::cout << "-----------------------------------------------------------\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
