#pragma once

class Being {
   private:
    int energy;

   public:
    Being(int e) : energy(e) {}
    virtual ~Being() {}

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