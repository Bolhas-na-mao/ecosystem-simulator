#pragma once
#include <iostream>

#include "Being.h"
#include "Fox.h"
#include "Grass.h"
#include "Rabbit.h"
#include "Random.h"

class World {
   public:
    World(int foxAmount, int rabbitAmount, int grassAmount) {
        for(int i = 0; i < 25; i++) {
            for(int j = 0; j < 25; j++) {
                cells[i][j] = nullptr;
            }
        }

        int x = 0;
        int y = 0;

        for(int i = 0; i < foxAmount; i++) {
            x = Random::getNumber(0, 24);
            y = Random::getNumber(0, 24);

            if(cells[x][y] == nullptr) {
                cells[x][y] = new Fox();
            } else {
                continue;
            }
        }

        for(int i = 0; i < rabbitAmount; i++) {
            x = Random::getNumber(0, 24);
            y = Random::getNumber(0, 24);

            if(cells[x][y] == nullptr) {
                cells[x][y] = new Rabbit();
            } else {
                continue;
            }
        }

        for(int i = 0; i < grassAmount; i++) {
            x = Random::getNumber(0, 24);
            y = Random::getNumber(0, 24);

            if(cells[x][y] == nullptr) {
                cells[x][y] = new Grass();
            } else {
                continue;
            }
        }
    };

    void addBeings() {

    };

   private:
    Being* cells[25][25];
};