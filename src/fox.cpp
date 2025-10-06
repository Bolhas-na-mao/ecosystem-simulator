#include "./entities/Fox.h"

#include <cmath>
#include <iostream>

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

    auto surroundings = world.checkSurroundings(this);

    auto myPos = world.find(this);

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
        World::SurroundingData* closest = nullptr;
        int minDistance = 0;

        for(auto& rabbitData : rabbits) {
            int dx = abs(rabbitData.x - myPos.x);
            int dy = abs(rabbitData.y - myPos.y);
            int distance = dx + dy;

            if(closest == nullptr || distance < minDistance) {
                minDistance = distance;
                closest = &rabbitData;
            }
        }

        int dx = closest->x - myPos.x;
        int dy = closest->y - myPos.y;

        if(abs(dx) <= 1 && abs(dy) <= 1) {
            world.eat(closest->entity, this);
            return;
        }

        int moveX = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
        int moveY = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;

        int newX = myPos.x + moveX;
        int newY = myPos.y + moveY;

        if(newX >= 0 && newX < World::SIZE && newY >= 0 && newY < World::SIZE) {
            Entity* occupant = world.check(newX, newY);

            if(occupant == nullptr) {
                world.move(this, {newX, newY});
            } else {
                std::vector<std::pair<int, int>> alternatives;

                for(int testX = -1; testX <= 1; testX++) {
                    for(int testY = -1; testY <= 1; testY++) {
                        if(testX == 0 && testY == 0)
                            continue;

                        int checkX = myPos.x + testX;
                        int checkY = myPos.y + testY;

                        if(checkX >= 0 && checkX < World::SIZE && checkY >= 0 &&
                           checkY < World::SIZE && world.check(checkX, checkY) == nullptr) {
                            alternatives.push_back({checkX, checkY});
                        }
                    }
                }

                if(!alternatives.empty()) {
                    std::pair<int, int> bestMove = alternatives[0];
                    int bestDist =
                        abs(closest->x - bestMove.first) + abs(closest->y - bestMove.second);

                    for(const auto& alt : alternatives) {
                        int dist = abs(closest->x - alt.first) + abs(closest->y - alt.second);
                        if(dist < bestDist) {
                            bestDist = dist;
                            bestMove = alt;
                        }
                    }

                    world.move(this, {bestMove.first, bestMove.second});
                }
            }
        }
    } else {
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
}