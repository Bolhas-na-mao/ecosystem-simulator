#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../utils/Random.h"
#include "Entity.h"
#include "Fox.h"
#include "Grass.h"
#include "Rabbit.h"

class World {
   private:
    struct Position {
        int x;
        int y;
    };
    static const int SIZE = 25;
    static const int VISIBILITY_RANGE = 8;

   public:
    Entity* grid[SIZE][SIZE];
    std::unordered_map<Entity*, Position> positions;

    World(int foxAmount, int rabbitAmount, int grassAmount) {
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                grid[i][j] = nullptr;
            }
        }

        int x = 0;
        int y = 0;

        for(int i = 0; i < foxAmount; i++) {
            x = Random::getNumber(0, SIZE - 1);
            y = Random::getNumber(0, SIZE - 1);

            if(grid[x][y] == nullptr) {
                grid[x][y] = new Fox();
                positions[grid[x][y]] = {x, y};
            } else {
                i--;
            }
        }

        for(int i = 0; i < rabbitAmount; i++) {
            x = Random::getNumber(0, SIZE - 1);
            y = Random::getNumber(0, SIZE - 1);

            if(grid[x][y] == nullptr) {
                grid[x][y] = new Rabbit();
                positions[grid[x][y]] = {x, y};
            } else {
                i--;
            }
        }

        for(int i = 0; i < grassAmount; i++) {
            x = Random::getNumber(0, SIZE - 1);
            y = Random::getNumber(0, SIZE - 1);

            if(grid[x][y] == nullptr) {
                grid[x][y] = new Grass();
                positions[grid[x][y]] = {x, y};
            } else {
                i--;
            }
        }
    };

    void move(Entity* e, Position newPos) {
        auto oldPos = positions[e];
        grid[oldPos.x][oldPos.y] = nullptr;
        grid[newPos.x][newPos.y] = e;
        positions[e] = newPos;
    }

    Position find(Entity* e) {
        return positions[e];
    }

    Entity* check(int x, int y) const {
        return grid[x][y];
    }

    std::vector<Entity*> checkSurroundings(Entity* e) {
        auto pos = positions[e];

        int startX = pos.x - VISIBILITY_RANGE;
        int endX = pos.x + VISIBILITY_RANGE;
        int startY = pos.y - VISIBILITY_RANGE;
        int endY = pos.y + VISIBILITY_RANGE;

        std::vector<Entity*> surroundings;

        for(int checkX = startX; checkX <= endX; checkX++) {
            for(int checkY = startY; checkY <= endY; checkY++) {
                if(checkX == pos.x && checkY == pos.y) {
                    continue;
                }

                bool isInBounds = checkX >= 0 && checkX < SIZE && checkY >= 0 && checkY < SIZE;

                if(isInBounds) {
                    surroundings.push_back(grid[checkX][checkY]);
                } else {
                    surroundings.push_back(nullptr);
                }
            }

            return surroundings;
        }
    }

    ~World() {
        std::unordered_set<Entity*> deleted;
        for(int i = 0; i < SIZE; ++i) {
            for(int j = 0; j < SIZE; ++j) {
                if(grid[i][j] != nullptr && deleted.find(grid[i][j]) == deleted.end()) {
                    deleted.insert(grid[i][j]);
                    delete grid[i][j];
                }
            }
        }
    }
};