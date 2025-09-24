#pragma once

class Being {
   private:
    bool isAlive = true;
    int energy;
    int ageInSeconds;

   public:
    Being(int e, int a) : energy(e), ageInSeconds(a) {}
};