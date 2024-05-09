#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Animal.h"
#include "Simulation.h"
using namespace std;

// Constructor.

Animal::Animal(char species, char ID, Location location, int eMax)
: Organism{species, ID, location}, m_maxEnergy{eMax}
{
    m_currentEnergy = eMax;
    srand(time(nullptr));
}

// Functions.

bool Animal::GetStatus()
{
    return m_dead;
}

Organism* Animal::SearchOrgs(Location lctn)
{
    for(int i = 0; i < simOrganisms.size(); i++)
    {
        Organism* org = simOrganisms[i];

        if(org != nullptr && org->GetID() != ' ')                 // Check if org is rendered to map.
        {
            if(org != this)
            {
                if(org->GetLocation().x == lctn.x && org->GetLocation().y == lctn.y)
                {
                    return org;                                 // Return pointer if m_location matches lctn arg.
                }
            }
        }
    }

    return nullptr;
}

void Animal::Consume()
{
    Organism* org = SearchOrgs(m_location);
    if(org != nullptr)
    {
        if(typeid(*org) == typeid(Plant))                       // If plant, cast and consume if grown.
        {
            Plant* plant = dynamic_cast<Plant*>(org);
            if(plant->GetStatus())
            {
                plant->Consumed();
                m_currentEnergy += plant->GetEnergy();
            }
        }
    }
}

void Animal::Death()                                            // Remove animal from sim.
{
    simMap[m_location.y][m_location.x] = ' ';
    m_id = ' ';
    m_dead = true;
}

int Animal::GetCurrentEnergy()
{
    return m_currentEnergy;
}

void Animal::PrintDetails()
{
    cout << "Species: " << m_species << '\n';
    cout << "ID: " << m_id << '\n';
    cout << "Current Energy: " << m_currentEnergy << '\n';
    cout << "Max Energy: " << m_maxEnergy << '\n';
    cout << "Location(x,y): " << '(' << m_location.x << ',' << m_location.y << ')' << '\n';
}

int RNG()                                           // Generate random number based on seed set at construction.
{
    int rN = rand()%4;
    return rN;
}

bool Animal::Edible(Organism* org)
{
    if(org != nullptr)                                              // Not null.
    {
        if(typeid(*org) == typeid(Plant))
        {
            Plant* plPtr = dynamic_cast<Plant*>(org);

            if(plPtr->GetStatus() && m_currentEnergy + plPtr->GetEnergy() < m_maxEnergy)        
            {
                return true;                                        // Grown and energy won't exceed max energy.
            }
            
            return false;
        }

        return false;
    }

    return false;
}

Location Animal::CheckForPredators()
{
    Location upDir{0,0};                                            // Initialize locations.
    Location downDir{0,0};
    Location leftDir{0,0};
    Location rightDir{0,0};

    Location upLoc{m_location.x, m_location.y -1};                  // Define relative to animal position.
    Location downLoc{m_location.x, m_location.y +1};
    Location leftLoc{m_location.x -1, m_location.y};
    Location rightLoc{m_location.x +1, m_location.y};

    Organism* upPtr = SearchOrgs(upLoc);                            // Find adjacent orgs by pointer.
    Organism* downPtr = SearchOrgs(downLoc);
    Organism* leftPtr = SearchOrgs(leftLoc);
    Organism* rightPtr = SearchOrgs(rightLoc);

    if(CheckOrgType(upPtr) == "Omnivore")                           // Change output based on presence of predators.
        upDir = {0,1};

    if(CheckOrgType(downPtr) == "Omnivore")
        downDir = {0,-1};

    if(CheckOrgType(leftPtr) == "Omnivore")
        leftDir = {1,0};

    if(CheckOrgType(rightPtr) == "Omnivore")
        rightDir = {-1,0};

    int outX = upDir.x + downDir.x + leftDir.x + rightDir.x;        // Assemble output.
    int outY = upDir.y + downDir.y + leftDir.y + rightDir.y;
    Location outDir{outX,outY};
    
    return outDir;
}

Location Animal::CheckForFood()
{
    Location upDir{0,0};                                            // Initialize locations.
    Location downDir{0,0};
    Location leftDir{0,0};
    Location rightDir{0,0};

    Location upLoc{m_location.x, m_location.y -1};                  // Define relative to animal position.
    Location downLoc{m_location.x, m_location.y +1};
    Location leftLoc{m_location.x -1, m_location.y};
    Location rightLoc{m_location.x +1, m_location.y};

    Organism* upPtr = SearchOrgs(upLoc);                            // Find adjacent orgs by pointer.
    Organism* downPtr = SearchOrgs(downLoc);
    Organism* leftPtr = SearchOrgs(leftLoc);
    Organism* rightPtr = SearchOrgs(rightLoc);

    if(Edible(upPtr) && simMap[upLoc.y][upLoc.x] != ' ')            // Change output based on presence of food.
        upDir = {0,-1};

    if(Edible(downPtr) && simMap[downLoc.y][downLoc.x] != ' ')
        downDir = {0,1};

    if(Edible(leftPtr) && simMap[leftLoc.y][leftLoc.x] != ' ')
        leftDir = {-1,0};

    if(Edible(rightPtr) && simMap[rightLoc.y][rightLoc.x] != ' ')
        rightDir = {1,0};

    int outX = upDir.x + downDir.x + leftDir.x + rightDir.x;        // Assemble output.
    int outY = upDir.y + downDir.y + leftDir.y + rightDir.y;
    Location outDir{outX,outY};
    return outDir;
}

Location Animal::CheckSurroundings()                                // Combine total output.
{
    Location predAvoid = CheckForPredators();
    Location foodDir = CheckForFood();
    
    int outX = predAvoid.x + foodDir.x;
    int outY = predAvoid.y + foodDir.y;

    Location outDir{outX,outY};
    return outDir;
}

void Animal::Move(Location direction)
{
    if(m_currentEnergy != 0)
    {
        int newX = m_location.x;
        int newY = m_location.y;
        int rowNum = simMap.size();
        int colNum = simMap[0].size();

        if(direction.x == 0 && direction.y == 0)                    // If no input, use random direction.
        {
            switch(RNG())
            {
                case 0:
                newY = newY +1;
                break;

                case 1:
                newY = newY -1;
                break;

                case 2:
                newX = newX -1;
                break;

                case 3:
                newX = newX +1;
                break;
            }
        }
        else
        {
            newX = m_location.x + direction.x;
            newY = m_location.y + direction.y;
        }

        if(newX >= 0 && newX < colNum && newY >= 0 && newY < rowNum)        // Check boundaries.
        {
            simMap[m_location.y][m_location.x] = ' ';
            SetLocation(newX, newY);
            simMap[m_location.y][m_location.x] = m_id;
        }

        m_currentEnergy--;
    }
    else                                                                    // If no energy, death.
    {
        Death();
    }
}

void Animal::Tick()
{
    if(!m_dead)
    {
        Location moveDir = CheckSurroundings();
        Consume();
        Move(moveDir);
    }
}