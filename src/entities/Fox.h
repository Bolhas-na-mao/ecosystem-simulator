#include "Being.h"

class Fox : public Being {
   public:
    Fox() : Being(100, 100) {}
    void reproduce() override {}
};