#include <emscripten.h>

#include <iostream>

#include "entities/Fox.h"
#include "entities/Grass.h"
#include "entities/Rabbit.h"
#include "entities/World.h"
#include "utils/Log.h"

World* gameWorld = nullptr;

extern "C" {
EMSCRIPTEN_KEEPALIVE
void initializeEcosystem() {
    if(gameWorld != nullptr) {
        delete gameWorld;
    }
    gameWorld = new World(15, 15, 15);
    std::cout << "Ecosystem initialized with 15 foxes, 15 rabbits, 15 grass!\n";
}

EMSCRIPTEN_KEEPALIVE
void tickEcosystem() {
    if(gameWorld != nullptr) {
        gameWorld->tick();
    }
}

EMSCRIPTEN_KEEPALIVE
int getEntityAt(int x, int y) {
    if(gameWorld == nullptr || x < 0 || x >= World::SIZE || y < 0 || y >= World::SIZE) {
        return 0;
    }

    Entity* entity = gameWorld->check(x, y);
    if(entity == nullptr) {
        return 0;
    } else if(dynamic_cast<Fox*>(entity)) {
        return 1;
    } else if(dynamic_cast<Rabbit*>(entity)) {
        return 2;
    } else if(dynamic_cast<Grass*>(entity)) {
        return 3;
    }
    return 0;
}

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