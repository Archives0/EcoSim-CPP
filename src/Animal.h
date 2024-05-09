#ifndef ANIMAL_H
#define ANIMAL_H
#include <iostream>
#include "Organism.h"
#include "Plant.h"
// #include "Simulation.h"
using namespace std;

class Plant;

class Animal : public Organism {
    protected:
    int m_maxEnergy{};
    int m_currentEnergy{};
    bool m_dead{false};
    virtual bool Edible(Organism* org);
    void Death();

    public:

    // Constructor.
    Animal(char species, char ID, Location location, int eMax);

    //Functions.
    bool GetStatus();
    Organism* SearchOrgs(Location lctn);
    virtual void Consume();
    int GetCurrentEnergy();
    virtual void PrintDetails();
    Location CheckForPredators();
    Location CheckForFood();
    Location CheckSurroundings();
    void Move(Location direction);
    virtual void Tick();
};
#endif