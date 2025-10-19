#include "Module3.hpp"
#include <algorithm>
#include <iomanip> // para std::setw y std::setfill

Module3::Module3() {}
Module3::~Module3() {}

void Module3::start() {}
void Module3::stop() {}

void Module3::deliver(const std::vector<unsigned char>& data) {
    std::lock_guard<std::mutex> lock(mtx);

    // Crear nuevo registro con timestamp actual
    Record rec;
    rec.data = data;
    rec.timestamp = std::chrono::system_clock::now();

    // Mantener buffer limitado a 100 elementos
    if(records.size() >= maxBuffer) {
        records.erase(records.begin()); // eliminar el más antiguo
    }
    records.push_back(rec);

    // Ordenar registros por timestamp (UTC)
    std::sort(records.begin(), records.end(), [](const Record &a, const Record &b) {
        return a.timestamp < b.timestamp;
    });

    // Imprimir todos los registros
    std::cout << " =========================== Module3 registros (" << records.size() << "):===========================\n";
    for(size_t i = 0; i < records.size(); ++i) {
        std::cout << "Array " << i << " tamaño: " << records[i].data.size() << " Datos: ";
        for(size_t j = 0; j < records[i].data.size(); ++j) {
            // Imprime cada byte en hexadecimal con 2 dígitos
            std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0')
                      << static_cast<int>(records[i].data[j]) << " ";
        }
        std::cout << std::dec << "\n"; // Volver a decimal para cualquier otro número
    }
}

void Module3::setNextModule(IModule* next) {
    (void)next; // Module3 es el último, no hay siguiente
}
