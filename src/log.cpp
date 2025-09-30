#include <iostream>

#include "entities/World.h"

// teste visual antes da implementação visual do ecosistema

void logWorld() {
    World ecosystem(15, 15, 15);

    for(int i = 0; i < 25; i++) {
        for(int j = 0; j < 25; j++) {
            Entity* cell = ecosystem.getCell(i, j);
            if(cell == nullptr) {
                std::cout << ". ";
            } else {
                std::cout << "X ";
            }
        }
        std::cout << "\n";
    }
}