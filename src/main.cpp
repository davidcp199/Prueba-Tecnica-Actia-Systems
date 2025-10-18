#include "Module1.hpp"
#include "Module2.hpp"
#include "Module3.hpp"
#include <thread>
#include <chrono>
#include <iostream>

int main() {
    std::cout << "Iniciando módulos...\n";

    // Crear módulos
    IModule* m1 = new Module1();
    IModule* m2 = new Module2();
    IModule* m3 = new Module3();

    // Conectar módulos
    m1->setNextModule(m2); // Module1 entrega datos a Module2
    m2->setNextModule(m3); // Module2 entrega datos a Module3

    // Iniciar módulos
    m1->start();
    m2->start();
    m3->start();

    std::cout << "Módulos corriendo durante 100 segundos...\n";
    std::this_thread::sleep_for(std::chrono::seconds(100));

    // Detener módulos
    m1->stop();
    m2->stop();
    m3->stop();

    // Liberar memoria
    delete m1;
    delete m2;
    delete m3;

    std::cout << "Ejecución finalizada.\n";
    return 0;
}
