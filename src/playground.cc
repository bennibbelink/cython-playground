#include <stdlib.h>
#include <iostream>
#include "playground.h"
#include "pyhooks.h"

void run_playground() {
    std::cout << "Running Playground..." << std::endl;
    std::cout << "Deleting agents..." << std::endl;
    int val = DelPyAgent();
    std::cout << "Return value: " << val << std::endl;
}