#pragma once

#include "Entity.h"

class Grass : public Entity {
   public:
    Grass() {}
    void update(World& world) override;
};