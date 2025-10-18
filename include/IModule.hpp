#pragma once
#include <vector>

class IModule {
public:
    virtual ~IModule() {}                     // destructor virtual obligatorio
    virtual void start() = 0;                 // método puro virtual
    virtual void stop() = 0;                  // método puro virtual
    virtual void deliver(const std::vector<unsigned char>& data) = 0;  // método puro virtual
};
