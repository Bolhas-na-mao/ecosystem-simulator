#pragma once

#include "Animal.h"

class Rabbit : public Animal {
   public:
    Rabbit() : Animal(10) {}
    void update(World& world) override;

   protected:
    Entity* createOffspring() override {
        return new Rabbit();
    }
};