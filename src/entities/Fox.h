#pragma once

#include "Animal.h"

class Fox : public Animal {
   public:
    Fox() : Animal(10) {}
    void update(World& world) override;
};