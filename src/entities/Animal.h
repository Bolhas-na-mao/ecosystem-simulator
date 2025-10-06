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

   protected:
    template <typename TargetType, typename SurroundingDataVec>
    bool moveTowardClosest(World& world, const SurroundingDataVec& targets);

    template <typename AnimalType>
    bool reproduce(World& world);
    virtual Entity* createOffspring() = 0;
};