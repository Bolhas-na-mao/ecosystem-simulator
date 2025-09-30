#pragma once

class Entity {
   public:
    virtual void update(class World& world) = 0;
    virtual ~Entity() default;
};