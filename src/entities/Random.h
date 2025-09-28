#include <iostream>
#include <random>

class Random {
   public:
    static int getNumber(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(gen);
    }

   private:
    static std::random_device rd;
    static std::mt19937 gen;
};

std::random_device Random::rd;
std::mt19937 Random::gen{Random::rd()};
