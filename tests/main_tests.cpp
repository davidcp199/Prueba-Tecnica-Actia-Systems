#include "Module1.hpp"
#include "Module2.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cassert>

// DummyReceiver simula Module3
class DummyReceiver : public IModule {
public:
    std::vector<std::vector<unsigned char>> received;

    void start() override {}
    void stop() override {}

    void deliver(const std::vector<unsigned char>& data) override {
        received.push_back(data);
    }
};

// -------------------------
// Test 1: Module1 genera arrays válidos
// -------------------------
void test_module1_basic() {
    std::cout << "Test 1: Generación de arrays aleatorios por Module1\n";

    DummyReceiver receiver;
    Module1 m1;
    m1.setNextModule(&receiver);

    m1.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    m1.stop();

    assert(!receiver.received.empty());

    // Comprobar tamaños y rangos de bytes
    for (const auto& array : receiver.received) {
        assert(array.size() >= 1 && array.size() <= 100);
        for (auto b : array)
            assert(b >= 0 && b <= 255);
    }

    std::cout << "Generados " << receiver.received.size()
              << " arrays válidos de tamaños 1-100 con bytes 0-255.\n\n";
}

// -------------------------
// Test 2: Module2 filtra patrón 0x00 0x01 0x02
// -------------------------
void test_module2_filter() {
    std::cout << "Test 2: Filtrado de patrón 0x00 0x01 0x02 por Module2\n";

    Module2 m2;
    DummyReceiver receiver;
    m2.setNextModule(&receiver);

    m2.start();

    // Array que contiene la secuencia
    std::vector<unsigned char> withPattern = {5, 0x00, 0x01, 0x02, 7};
    // Array que no contiene la secuencia
    std::vector<unsigned char> noPattern = {10, 11, 12};

    m2.deliver(withPattern);
    m2.deliver(noPattern);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    m2.stop();

    assert(receiver.received.size() == 1);
    const auto& passed = receiver.received.front();
    assert(passed.size() == withPattern.size());
    assert(passed[1] == 0x00 && passed[2] == 0x01 && passed[3] == 0x02);

    std::cout << "Filtrado correcto. Solo pasó el array con la secuencia.\n\n";
}


// -------------------------
int main() {
    test_module1_basic();
    test_module2_filter();

    std::cout << "---------------------------------\n";
    std::cout << "Todos los tests pasaron correctamente.\n";
    std::cout << "---------------------------------\n";
    return 0;
}
