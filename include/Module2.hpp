#ifndef MODULE2_H
#define MODULE2_H

#include "IModule.hpp"
#include <thread>
#include <queue>
#include <mutex>
#include <atomic>
#include <vector>

class Module2 : public IModule {
public:
    Module2();
    ~Module2();

    void start() override;
    void stop() override;
    void deliver(const std::vector<unsigned char>& data) override;

    void setNextModule(IModule* next);

private:
    void run();

    std::thread worker;
    std::atomic<bool> running;
    std::queue<std::vector<unsigned char> > buffer;
    std::mutex bufferMutex;

    IModule* nextModule;
};

#endif
 // MODULE2_H
