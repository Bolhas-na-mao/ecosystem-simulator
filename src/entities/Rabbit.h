#include "Being.h"

class Rabbit : public Being {
   public:
    Rabbit() : Being(100, 100) {}
    void reproduce() override {}
};