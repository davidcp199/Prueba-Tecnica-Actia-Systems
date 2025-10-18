#ifndef MODULE1_H
#define MODULE1_H

#include "IModule.hpp"
#include <thread>
#include <vector>
#include <ostream>

class Module1 : public IModule {
public:
    Module1(std::ostream &outStream);
    ~Module1();

    void start();
    void stop();
    void deliver(const std::vector<unsigned char>& data);

private:
    void run();
    std::ostream &out;
    std::thread worker;
    bool running;
};

#endif // MODULE1_H
