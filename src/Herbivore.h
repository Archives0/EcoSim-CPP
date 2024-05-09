#ifndef HERBIVORE_H
#define HERBIVORE_H
#include <iostream>
#include "Animal.h"
using namespace std;

class Herbivore : public Animal {
    public:
    Herbivore(char species, char ID, Location location, int eMax)
    : Animal{species, ID, location, eMax}
    {}

    virtual void Tick();
};
#endif