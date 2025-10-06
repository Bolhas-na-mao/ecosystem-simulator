#pragma once
#include <cmath>
#include <vector>

#include "Animal.h"
#include "World.h"

template <typename TargetType, typename SurroundingDataVec>
bool Animal::moveTowardClosest(World& world, const SurroundingDataVec& targets) {
    if(targets.empty()) {
        return false;
    }

    auto myPos = world.find(this);

    const World::SurroundingData* closest = nullptr;
    int minDistance = 0;

    for(const auto& targetData : targets) {
        int dx = abs(targetData.x - myPos.x);
        int dy = abs(targetData.y - myPos.y);
        int distance = dx + dy;

        if(closest == nullptr || distance < minDistance) {
            minDistance = distance;
            closest = &targetData;
        }
    }

    int dx = closest->x - myPos.x;
    int dy = closest->y - myPos.y;

    bool hasAdjacent = abs(dx) <= 1 && abs(dy) <= 1;

    if(abs(dx) <= 1 && abs(dy) <= 1) {
        Entity* target = world.check(closest->x, closest->y);

        bool isTargetStillThere = target != nullptr && dynamic_cast<TargetType*>(target) != nullptr;

        if(isTargetStillThere) {
            world.eat(target, this);
            return true;
        }
    }

    int moveX = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
    int moveY = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;

    int newX = myPos.x + moveX;
    int newY = myPos.y + moveY;

    if(newX >= 0 && newX < World::SIZE && newY >= 0 && newY < World::SIZE) {
        Entity* occupant = world.check(newX, newY);

        if(occupant == nullptr) {
            world.move(this, {newX, newY});
            return true;
        } else {
            std::vector<std::pair<int, int>> alternatives;

            for(int testX = -1; testX <= 1; testX++) {
                for(int testY = -1; testY <= 1; testY++) {
                    if(testX == 0 && testY == 0)
                        continue;

                    int checkX = myPos.x + testX;
                    int checkY = myPos.y + testY;

                    if(checkX >= 0 && checkX < World::SIZE && checkY >= 0 && checkY < World::SIZE &&
                       world.check(checkX, checkY) == nullptr) {
                        alternatives.push_back({checkX, checkY});
                    }
                }
            }

            if(!alternatives.empty()) {
                std::pair<int, int> bestMove = alternatives[0];
                int bestDist = abs(closest->x - bestMove.first) + abs(closest->y - bestMove.second);

                for(const auto& alt : alternatives) {
                    int dist = abs(closest->x - alt.first) + abs(closest->y - alt.second);
                    if(dist < bestDist) {
                        bestDist = dist;
                        bestMove = alt;
                    }
                }

                world.move(this, {bestMove.first, bestMove.second});
                return true;
            }
        }
    }

    return false;
}