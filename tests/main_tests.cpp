#include "Utils.hpp"
#include "Module1.hpp"
#include <sstream>
#include <vector>
#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>

// Test de enviar y recibir un vector simple
void test_send_receive_TCP() {
    // Vector original y enviar datos
    std::vector<unsigned char> original;
    original.push_back(0);
    original.push_back(1);
    original.push_back(2);
    original.push_back(255);
    original.push_back(128);
    original.push_back(64);

    std::ostringstream buffer;

    send_TCP(buffer, original);

    // Recibir datos
    std::vector<unsigned char> recibido;
    std::istringstream input(buffer.str());
    receive_TCP(input, recibido);

    // Comprobar que tamaño y contenido son iguales
    assert(original.size() == recibido.size());
    for(int i = 0; i < (int)original.size(); ++i)
        assert(original[i] == recibido[i]);

    std::cout << "test_send_receive_TCP PASADO\n";
}

// Test de Module1 generando arrays y enviándolos a un buffer
void test_module1_generation() {
    std::ostringstream buffer;   // Buffer resutlados
    Module1 m1(buffer);

    // Empezar y generar datos
    m1.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    m1.stop();

    std::cout << "test_module1_generation PASADO. Bytes generados: "
              << buffer.str().size() << "\n";

    // Leer datos generados
    std::istringstream input(buffer.str());
    for(int i = 0; i < 3; ++i) {
        std::vector<unsigned char> data;
        receive_TCP(input, data);
        std::cout << "Array " << i << " recibido, tamaño: " << data.size() << "\n";
    }
}

int main() {
    test_send_receive_TCP();
    test_module1_generation();

    std::cout << "Todos los tests pasados correctamente.\n";
    return 0;
}
