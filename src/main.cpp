#include <iostream>
#include <emscripten.h>

using namespace std;

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void hello_ecosystem() {
        cout << "Ecosystem Simulator initialized!\n";
    }
}

int main() {
    cout << "Starting ecosystem simulator...\n";
    return 0;
}