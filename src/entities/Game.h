#pragma once
#include <Being.h>

class Game {
   public:
    Game() {
        for(int i = 0; i < 25; i++) {
            for(int j = 0; j < 25; j++) {
                cells[i][j] = nullptr;
            }
        }
    }

   private:
    Being* cells[25][25];
};