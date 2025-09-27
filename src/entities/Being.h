#pragma once

class Being {
   private:
    bool isAlive = true;
    int energy;
    int ageInSeconds;

   public:
    Being(int e, int a) : energy(e), ageInSeconds(a) {}
    virtual ~Being() {}

    virtual void reproduce() = 0;

    int getEnergy() {
        return energy;
    }

    void increaseEnergy() {
        energy++;
    }

    void decreaseEnergy() {
        energy--;
    }
};