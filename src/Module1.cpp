#include "Module1.hpp"
#include "Utils.hpp"
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

Module1::Module1(std::ostream &outStream)
    : out(outStream), running(false) {
    std::srand(std::time(0)); // semilla para rand()
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
    if(worker.joinable())
        worker.join();
}

void Module1::deliver(const std::vector<unsigned char>&) {
    // no hace nada
}

void Module1::run() {
    while(running) {
        int size = 1 + std::rand() % 100; // tamaño 1-100
        std::vector<unsigned char> data(size);
        for(int i = 0; i < size; ++i) {
            data[i] = std::rand() % 256;  // byte aleatorio 0-255
        }

        send_TCP(out, data);  // enviar al buffer
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
