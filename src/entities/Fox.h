#include "Animal.h"

class Fox : public Animal {
   public:
    Fox() : Animal(100) {}
    void update(class World& world) override {}
};