#include "Utils.hpp"
#include <sstream>
#include <iostream>

int main() {
    std::vector<unsigned char> send_data = {10,20,30,40};
    std::ostringstream buf;
    send_TCP(buf, send_data);

    std::vector<unsigned char> recv_data;
    std::istringstream input(buf.str());
    receive_TCP(input, recv_data);

    std::cout << "Bytes recibidos: " << recv_data.size() << std::endl;
    for (auto b : recv_data) std::cout << (int)b << " ";
    std::cout << std::endl;
    return 0;
}
