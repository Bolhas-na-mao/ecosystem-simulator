#include <emscripten.h>

#include <iostream>

extern "C" {
EMSCRIPTEN_KEEPALIVE
void hello_ecosystem() {
    std::cout << "Ecosystem Simulator initialized!\n";
}
}

int main() {
    std::cout << "Starting ecosystem simulator...\n";
    return 0;
}