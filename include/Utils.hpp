#pragma once
#include <vector>
#include <ostream>
#include <istream>

// Envia un vector de bytes a un stream.
// Primero envia el tamaño y luego los datos.
void send_TCP(std::ostream &out, const std::vector<unsigned char> &data);

// Recibe un vector de bytes de un stream.
// Primero lee el tamaño y luego los datos.
void receive_TCP(std::istream &in, std::vector<unsigned char> &data);
