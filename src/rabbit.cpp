#include "./entities/Rabbit.h"

#include <iostream>

#include "./entities/World.h"

void Rabbit::update(World& world) {
    auto surroundings = world.checkSurroundings(this);
    std::cout << "surroundings of Rabbit: " << surroundings.size() << std::endl;
}