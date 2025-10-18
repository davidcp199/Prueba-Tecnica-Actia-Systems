#include "Utils.hpp"
#include <iostream>
#include <vector>

void send_TCP(std::ostream &out, const std::vector<unsigned char> &data) {
    unsigned int size = data.size();

    // Enviar tamaño
    out.write((char*)&size, sizeof(size));

    // Enviar datos
    for (unsigned int i = 0; i < size; ++i) {
        out.put(data[i]);
    }

    out.flush();
}

void receive_TCP(std::istream &in, std::vector<unsigned char> &data) {
    unsigned int size = 0;

    // Leer tamaño
    in.read((char*)&size, sizeof(size));

    data.resize(size);

    // Leer datos
    for (unsigned int i = 0; i < size; ++i) {
        data[i] = in.get();
    }
}
