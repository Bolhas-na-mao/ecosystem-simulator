#include "./entities/Fox.h"

#include <cmath>
#include <iostream>

#include "./entities/Animal.inl"
#include "./entities/Rabbit.h"
#include "./entities/World.h"
#include "./utils/Random.h"

void Fox::update(World& world) {
    decreaseEnergy();

    int energy = getEnergy();

    if(energy <= 0) {
        world.kill(this);
        return;
    }

    if(energy >= 10) {
        reproduce<Fox>(world);
    }

    auto surroundings = world.checkSurroundings(this);

    std::vector<World::SurroundingData> rabbits;

    for(const auto& data : surroundings) {
        if(!data.entity || !data.isInBounds) {
            continue;
        }

        Rabbit* rabbit = dynamic_cast<Rabbit*>(data.entity);
        if(rabbit != nullptr) {
            rabbits.push_back(data);
        }
    }

    if(!rabbits.empty()) {
        if(moveTowardClosest<Rabbit>(world, rabbits)) {
            return;
        }
    }

    auto myPos = world.find(this);
    std::vector<std::pair<int, int>> availableMoves;

    for(int dx = -1; dx <= 1; dx++) {
        for(int dy = -1; dy <= 1; dy++) {
            if(dx == 0 && dy == 0)
                continue;

            int checkX = myPos.x + dx;
            int checkY = myPos.y + dy;

            if(checkX >= 0 && checkX < World::SIZE && checkY >= 0 && checkY < World::SIZE &&
               world.check(checkX, checkY) == nullptr) {
                availableMoves.push_back({checkX, checkY});
            }
        }
    }

    if(!availableMoves.empty()) {
        int randomIndex = Random::getNumber(0, availableMoves.size() - 1);
        auto randomMove = availableMoves[randomIndex];
        world.move(this, {randomMove.first, randomMove.second});
    }
}