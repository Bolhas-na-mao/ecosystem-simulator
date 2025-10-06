#pragma once
#include "Entity.h"

class Animal : public Entity {
   private:
    int energy;

   public:
    Animal(int e) : energy(e) {}
    virtual ~Animal() {}

    int getEnergy() {
        return energy;
    }

    void increaseEnergy(int e) {
        energy = energy + e;
    }

    void decreaseEnergy() {
        energy--;
    }
};