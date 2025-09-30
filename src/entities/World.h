#pragma once

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
            } else {
                i--;
            }
        }

        for(int i = 0; i < rabbitAmount; i++) {
            x = Random::getNumber(0, SIZE - 1);
            y = Random::getNumber(0, SIZE - 1);

            if(grid[x][y] == nullptr) {
                grid[x][y] = new Rabbit();
            } else {
                i--;
            }
        }

        for(int i = 0; i < grassAmount; i++) {
            x = Random::getNumber(0, SIZE - 1);
            y = Random::getNumber(0, SIZE - 1);

            if(grid[x][y] == nullptr) {
                grid[x][y] = new Grass();
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
}