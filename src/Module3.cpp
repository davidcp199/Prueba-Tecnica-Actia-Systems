#include "Module3.hpp"
#include <iostream>
#include <iomanip>
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
    if(worker.joinable()) worker.join();
}

void Module3::deliver(const std::vector<unsigned char>& data) {
    std::lock_guard<std::mutex> lock(buffer_mutex);
    Record rec;
    rec.data = data;
    rec.timestamp = std::chrono::system_clock::now();
    buffer.push(rec);
}

void Module3::setNextModule(IModule* next) {
    (void)next;
}

void Module3::run() {
    while(running) {
        Record rec;
        bool hayDato = false;

        // Sacar un dato del buffer
        std::lock_guard<std::mutex> lock(buffer_mutex);
        if (!buffer.empty()) {
            rec = buffer.front();
            buffer.pop();
            hayDato = true;
        }


        if(hayDato) {
            // Agregar a registros
            if(records.size() >= maxBuffer) {
                records.erase(records.begin());
            }
            records.push_back(rec);

            // Ordenar por timestamp
            for(size_t i = 0; i < records.size(); i++) {
                for(size_t j = i+1; j < records.size(); j++) {
                    if(records[j].timestamp < records[i].timestamp) {
                        Record tmp = records[i];
                        records[i] = records[j];
                        records[j] = tmp;
                    }
                }
            }

            // Imprimir registros
            std::cout << "================ Module3 registros (" << records.size() << ") ==================\n";
            for(size_t i = 0; i < records.size(); i++) {
                std::cout << "Array " << i << " tamaño: " << records[i].data.size() << " Datos: ";
                for(size_t j = 0; j < records[i].data.size(); j++) {
                    int val = (int)records[i].data[j];
                    if(val < 16) std::cout << "0";
                    std::cout << std::hex << val << " ";
                }
                std::cout << std::dec << "\n";
            }
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}
