#include "Being.h"

class Grass : public Being {
   public:
    Grass() : Being(100, 100) {}
    void reproduce() override {}
};