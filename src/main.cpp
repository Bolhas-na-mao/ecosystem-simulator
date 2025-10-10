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
int countEntityType(int entityType) {
    if(gameWorld == nullptr) {
        return 0;
    }

    int count = 0;
    for(int i = 0; i < World::SIZE; i++) {
        for(int j = 0; j < World::SIZE; j++) {
            Entity* entity = gameWorld->check(i, j);
            if(entity != nullptr) {
                if(entityType == 1 && dynamic_cast<Fox*>(entity)) {
                    count++;
                } else if(entityType == 2 && dynamic_cast<Rabbit*>(entity)) {
                    count++;
                } else if(entityType == 3 && dynamic_cast<Grass*>(entity)) {
                    count++;
                }
            }
        }
    }
    return count;
}

EMSCRIPTEN_KEEPALIVE
void placeEntity(int x, int y, int entityType) {
    if(gameWorld == nullptr || x < 0 || x >= World::SIZE || y < 0 || y >= World::SIZE) {
        return;
    }

    if(gameWorld->check(x, y) != nullptr) {
        return;
    }

    Entity* newEntity = nullptr;
    if(entityType == 1) {
        newEntity = new Fox();
    } else if(entityType == 2) {
        newEntity = new Rabbit();
    } else if(entityType == 3) {
        newEntity = new Grass();
    }

    if(newEntity != nullptr) {
        gameWorld->grid[x][y] = newEntity;
        gameWorld->positions[newEntity] = {x, y};
    }
}

EMSCRIPTEN_KEEPALIVE
void removeEntity(int x, int y) {
    if(gameWorld == nullptr || x < 0 || x >= World::SIZE || y < 0 || y >= World::SIZE) {
        return;
    }

    Entity* entity = gameWorld->check(x, y);
    if(entity != nullptr) {
        gameWorld->positions.erase(entity);
        delete entity;
        gameWorld->grid[x][y] = nullptr;
    }
}

EMSCRIPTEN_KEEPALIVE
void replaceEntity(int x, int y, int entityType) {
    if(gameWorld == nullptr || x < 0 || x >= World::SIZE || y < 0 || y >= World::SIZE) {
        return;
    }

    removeEntity(x, y);

    Entity* newEntity = nullptr;
    if(entityType == 1) {
        newEntity = new Fox();
    } else if(entityType == 2) {
        newEntity = new Rabbit();
    } else if(entityType == 3) {
        newEntity = new Grass();
    }

    if(newEntity != nullptr) {
        gameWorld->grid[x][y] = newEntity;
        gameWorld->positions[newEntity] = {x, y};
    }
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