#include <iostream>
#include <emscripten.h>

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void hello_ecosystem() {
        std::cout << "Ecosystem Simulator initialized!" << std::endl;
    }
}

int main() {
    std::cout << "Starting ecosystem simulator..." << std::endl;
    return 0;
}