#pragma once

#include "../utils/Random.h"
#include "Entity.h"
#include "Fox.h"
#include "Grass.h"
#include "Rabbit.h"

class World {
   private:
    int size = 25;

   public:
    World(int foxAmount, int rabbitAmount, int grassAmount) {
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                cells[i][j] = nullptr;
            }
        }

        int x = 0;
        int y = 0;

        for(int i = 0; i < foxAmount; i++) {
            x = Random::getNumber(0, size - 1);
            y = Random::getNumber(0, size - 1);

            if(cells[x][y] == nullptr) {
                cells[x][y] = new Fox();
            } else {
                i--;
            }
        }

        for(int i = 0; i < rabbitAmount; i++) {
            x = Random::getNumber(0, size - 1);
            y = Random::getNumber(0, size - 1);

            if(cells[x][y] == nullptr) {
                cells[x][y] = new Rabbit();
            } else {
                i--;
            }
        }

        for(int i = 0; i < grassAmount; i++) {
            x = Random::getNumber(0, 24);
            y = Random::getNumber(0, 24);

            if(cells[x][y] == nullptr) {
                cells[x][y] = new Grass();
            } else {
                i--;
            }
        }
    };

    Entity* getCell(int x, int y) const {
        return cells[x][y];
    }

    ~World() {
        for(int i = 0; i < size; ++i)
            for(int j = 0; j < size; ++j)
                delete cells[i][j];
    };

   private:
    Entity* cells[size][size];
};