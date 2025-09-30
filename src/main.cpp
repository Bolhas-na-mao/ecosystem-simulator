#include <emscripten.h>

#include <iostream>

#include "utils/Log.h"

extern "C" {
EMSCRIPTEN_KEEPALIVE
void hello_ecosystem() {
    std::cout << "Ecosystem Simulator initialized!\n";

    logWorld();
}
}

int main() {
    std::cout << "Starting ecosystem simulator...\n";
    return 0;
}