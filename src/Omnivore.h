#ifndef OMNIVORE_H
#define OMNIVORE_H
#include <iostream>
#include "Animal.h"
using namespace std;

class Omnivore : public Animal {
    protected:
    virtual bool Edible(Organism* org);

    public:
    Omnivore(char species, char ID, Location location, int eMax)
    : Animal{species, ID, location, eMax}
    {}

    virtual void Consume();
    virtual void Tick();
};
#endif