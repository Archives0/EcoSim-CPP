#include <iostream>
#include "Animal.h"
#include "Herbivore.h"
#include "Omnivore.h"
using namespace std;

bool Omnivore::Edible(Organism* org)
{
    if(org != nullptr)
    {
        if(typeid(*org) == typeid(Plant))                           // Check if org is plant.
        {
            Plant* plPtr = dynamic_cast<Plant*>(org);

            if(m_currentEnergy + plPtr->GetEnergy() < m_maxEnergy)
            {
                return true;
            }
            return false;
        }
        else if(typeid(*org) == typeid(Animal))                     // Add animal to Edible check.
        {
            Animal* anPtr = dynamic_cast<Animal*>(org);

            if(m_currentEnergy + anPtr->GetCurrentEnergy() < m_maxEnergy)
            {
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

void Omnivore::Consume()
{
    Organism* org = SearchOrgs(m_location);
    if(org != nullptr)
    {
        if(typeid(*org) == typeid(Plant))
        {
            Plant* plant = dynamic_cast<Plant*>(org);
            if(plant->GetStatus())
            {
                plant->Consumed();
                m_currentEnergy += plant->GetEnergy();
            }
        }
        else if(typeid(*org) == typeid(Herbivore))                   // Add herbivore alternative.
        {
            Herbivore* herb = dynamic_cast<Herbivore*>(org);
            if(!herb->GetStatus())
            {
                herb->Consumed();
                m_currentEnergy += herb->GetCurrentEnergy();
            }
        }
    }
}

void Omnivore::Tick()
{
    if(!m_dead)
    {
        Location moveDir = CheckSurroundings();
        Consume();
        Move(moveDir);
    }
}