#include "./entities/Grass.h"

#include <iostream>

#include "./entities/World.h"

void Grass::update(World& world) {
    auto surroundings = world.checkSurroundings(this);
    std::cout << "surroundings of Grass: " << surroundings.size() << std::endl;
}