#include <iostream>
#include "src/core/Application.h"


using namespace lc;

int main() {
    try {
        lc::Application::initialize();
        lc::Application::startup();
    } catch (std::exception& error) {
        std::cout << "Error: " << error.what() << std::endl;
    }
    return 0;
}

