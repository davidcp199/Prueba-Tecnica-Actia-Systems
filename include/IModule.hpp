#pragma once
#include <vector>

class IModule {
public:
    virtual ~IModule() {}
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void deliver(const std::vector<unsigned char>& data) = 0;
};
