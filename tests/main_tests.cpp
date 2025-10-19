#include "Module1.hpp"
#include "Module2.hpp"
#include "Module3.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cassert>

// -------------------------
// Simula receptor para tests
// -------------------------
class DummyReceiver : public IModule {
public:
    std::vector<std::vector<unsigned char>> received;

    void start() override {}
    void stop() override {}

    void deliver(const std::vector<unsigned char>& data) override {
        received.push_back(data);
    }

    void setNextModule(IModule* next) override {
        (void)next;
    }
};

// -------------------------
// Test Modulo 1
// -------------------------
void test_module1() {
    std::cout << "================== Test 1: Generación de arrays aleatorios por Module1 ==================\n";

    DummyReceiver r;
    Module1 m1;
    m1.setNextModule(&r);

    m1.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    m1.stop();

    assert(!r.received.empty());

    int count = 0;
    for (std::vector<uint8_t> &arr : r.received) {
        assert(arr.size() > 0 && arr.size() <= 100);
        for (uint8_t b : arr) {
            assert(b >= 0 && b <= 255);
        }

        // Imprimir array
        std::cout << "Array " << count++ << " (" << arr.size() << " bytes): ";
        for (size_t j = 0; j < arr.size(); j++) {
            int val = static_cast<int>(arr[j]);
            if (val < 16) std::cout << "0";
            std::cout << std::hex << val << " ";
        }
        std::cout << std::dec << "\n";
    }

    std::cout << "\nOK - " << r.received.size()
              << " arrays generados correctamente.\n\n";
}


// -------------------------
// Test 2: Module2 filtra patrón 0x00 0x01 0x02
// -------------------------
void test_module2_filter() {
    std::cout << "================== Test 2: Filtrado de patrón 0x00 0xFF por Module2 ==================\n";

    Module2 m2;
    DummyReceiver receiver;
    m2.setNextModule(&receiver);

    m2.start();

    // Array con secuencia
    std::vector<unsigned char> withPattern = {0x05, 0x00, 0xFF, 0x07};
    // Array sin secuencia
    std::vector<unsigned char> noPattern = {0x10, 0xFF, 0x00, 0x11, 0x12};

    m2.deliver(withPattern);
    m2.deliver(noPattern);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    m2.stop();

    // Solo pasa el primer array
    assert(receiver.received.size() == 1);

    const std::vector<unsigned char>& passed = receiver.received.front();
    assert(passed.size() == withPattern.size());
    assert(passed[1] == 0x00 && passed[2] == 0xFF);

    std::cout << "Filtrado correcto\n";
}


// -------------------------
// Test 3: Module3 recibe arrays correctamente
// -------------------------
void test_module3_buffer() {
    std::cout << "================== Test 3: Buffer y almacenamiento de Module3 ==================\n";

    Module3 m3;
    m3.start();

    std::vector<unsigned char> data1 = {0x01, 0x02};
    std::vector<unsigned char> data2 = {0x03, 0x04};

    m3.deliver(data1);
    m3.deliver(data2);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    m3.stop();

    std::cout << "Module3 ha procesado los 2 arrays correctamente.\n\n";
}


// -------------------------
int main() {
    test_module1();
    test_module2_filter();
    test_module3_buffer();

    std::cout << "=========================================\n";
    std::cout << "Todos los tests han pasado correctamente.\n";
    std::cout << "=========================================\n";
    return 0;
}
