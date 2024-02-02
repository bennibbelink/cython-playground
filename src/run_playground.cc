#include <stdlib.h>
#include <iostream>
#include "run_playground.h"
#include "pyhooks.h"

void run_playground() {
    std::cout << "Calling PyStart()..." << std::endl;
    PyStart();
    std::cout << "Running Playground..." << std::endl;
    std::cout << "Deleting agents..." << std::endl;
    int val = DelPyAgent();
    std::cout << "Return value: " << val << std::endl;
}