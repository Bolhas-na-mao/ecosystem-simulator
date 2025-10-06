#pragma once

#include <functional>
#include <stdexcept>
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
    std::unordered_set<Entity*> entitiesToDelete;
    struct Position {
        int x = 0;
        int y = 0;
    };

    void placeEntities(int count, std::function<Entity*()> createEntity) {
        for(int i = 0; i < count; i++) {
            int x = Random::getNumber(0, SIZE - 1);
            int y = Random::getNumber(0, SIZE - 1);

            if(grid[x][y] == nullptr) {
                grid[x][y] = createEntity();
                positions[grid[x][y]] = {x, y};
            } else {
                i--;
            }
        }
    };

    static const int VISIBILITY_RANGE = 8;

   public:
    static const int SIZE = 25;
    Entity* grid[SIZE][SIZE];
    std::unordered_map<Entity*, Position> positions;

    struct SurroundingData {
        Entity* entity;
        bool isInBounds;
        int x;
        int y;
    };

    World(int foxAmount, int rabbitAmount, int grassAmount) {
        if(foxAmount + rabbitAmount + grassAmount > SIZE * SIZE) {
            throw std::invalid_argument("Too many entities for grid size");
        }

        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                grid[i][j] = nullptr;
            }
        }

        placeEntities(foxAmount, []() { return new Fox(); });
        placeEntities(rabbitAmount, []() { return new Rabbit(); });
        placeEntities(grassAmount, []() { return new Grass(); });
    };

    void tick() {
        entitiesToDelete.clear();

        std::vector<Entity*> allEntities;
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                if(grid[i][j] != nullptr) {
                    allEntities.push_back(grid[i][j]);
                }
            }
        }

        for(Entity* e : allEntities) {
            if(entitiesToDelete.find(e) == entitiesToDelete.end()) {
                e->update(*this);
            }
        }

        for(Entity* e : entitiesToDelete) {
            auto entityPos = find(e);
            grid[entityPos.x][entityPos.y] = nullptr;
            positions.erase(e);
            delete e;
        }
        entitiesToDelete.clear();
    }

    void move(Entity* e, Position newPos) {
        auto oldPos = positions[e];
        grid[oldPos.x][oldPos.y] = nullptr;
        grid[newPos.x][newPos.y] = e;
        positions[e] = newPos;
    }

    void eat(Entity* prey, Entity* predator) {
        auto preyPos = find(prey);

        kill(prey);

        move(predator, preyPos);

        Animal* predatorAnimal = dynamic_cast<Animal*>(predator);
        if(predatorAnimal) {
            predatorAnimal->increaseEnergy();
        }
    }

    void kill(Entity* entity) {
        entitiesToDelete.insert(entity);
    }

    Position find(Entity* e) {
        return positions[e];
    }

    Entity* check(int x, int y) const {
        return grid[x][y];
    }

    std::vector<SurroundingData> checkSurroundings(Entity* e) const {
        if(!e)
            return {};
        auto it = positions.find(e);
        if(it == positions.end())
            return {};
        const auto& pos = it->second;

        int startX = pos.x - VISIBILITY_RANGE;
        int endX = pos.x + VISIBILITY_RANGE;
        int startY = pos.y - VISIBILITY_RANGE;
        int endY = pos.y + VISIBILITY_RANGE;

        std::vector<SurroundingData> surroundings;

        for(int checkX = startX; checkX <= endX; checkX++) {
            for(int checkY = startY; checkY <= endY; checkY++) {
                if(checkX == pos.x && checkY == pos.y) {
                    continue;
                }

                bool isInBounds = checkX >= 0 && checkX < SIZE && checkY >= 0 && checkY < SIZE;

                surroundings.push_back(
                    {isInBounds ? grid[checkX][checkY] : nullptr, isInBounds, checkX, checkY});
            }
        }
        return surroundings;
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