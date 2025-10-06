#include "./entities/Fox.h"

#include <iostream>

#include "./entities/World.h"

void Fox::update(World& world) {
    auto surroundings = world.checkSurroundings(this);
    std::cout << "surroundings of fox: " << surroundings.size() << std::endl;
}