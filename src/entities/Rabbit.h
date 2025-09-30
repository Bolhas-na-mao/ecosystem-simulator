#include "Animal.h"

class Rabbit : public Animal {
   public:
    Rabbit() : Animal(100) {}
    void update(class World& world) override {}
};