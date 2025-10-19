#include "Module1.hpp"
#include "Module2.hpp"
#include "Module3.hpp"
#include <thread>
#include <chrono>
#include <iostream>

int main(void) {
    //Create modules
    IModule* m1 = new Module1();
    IModule* m2 = new Module2();
    IModule* m3 = new Module3();

    //Set m1 to deliver data to m2
    m1->setNextModule(m2);

    //Set m2 to deliver data to m3
    m2->setNextModule(m3);

    //Start modules
    m1->start();
    m2->start();
    m3->start();

    //Wait 100 seconds
    std::this_thread::sleep_for(std::chrono::seconds(100));

    //Wait 100 seconds
    m1->stop();
    m2->stop();
    m3->stop();

    //Release modules
    delete m1;
    delete m2;
    delete m3;
    return 0;
}
