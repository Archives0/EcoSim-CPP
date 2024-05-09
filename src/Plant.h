#ifndef PLANT_H
#define PLANT_H
#include <iostream>
#include "Organism.h"
using namespace std;

class Plant : public Organism {
    private:
    int m_growthCo{};
    int m_energyPoints{};
    int m_timer{0};
    bool m_grown = true;

    public:
    Plant(char species, char ID, Location location, int growthCoef, int energy);
    virtual void Consumed();
    // void CheckEaten();
    bool GetStatus();
    int GetEnergy();
    void Grow();
    virtual void PrintDetails();
    virtual void Tick();
};
#endif