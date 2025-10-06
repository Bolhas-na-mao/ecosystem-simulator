#include <iostream>

#include "entities/World.h"

// teste visual antes da implementação visual do ecosistema

World ecosystem(15, 15, 15);
bool isFirstTime = true;

void logWorld() {
    if(isFirstTime) {
        isFirstTime = false;
    } else {
        ecosystem.tick();
    }

    for(int i = 0; i < 25; i++) {
        for(int j = 0; j < 25; j++) {
            Entity* entity = ecosystem.check(i, j);
            if(dynamic_cast<Rabbit*>(entity)) {
                std::cout << "R ";
            } else if(dynamic_cast<Grass*>(entity)) {
                std::cout << "G ";
            } else if(dynamic_cast<Fox*>(entity)) {
                std::cout << "F ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
}