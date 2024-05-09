#include <iostream>
#include "Plant.h"
#include "Simulation.h"
using namespace std;

Plant::Plant(char species, char ID, Location location, int growthCoef, int energy)
: Organism{species, ID, location}, m_growthCo{growthCoef}, m_energyPoints{energy}
{}

int Plant::GetEnergy()
{
    return m_energyPoints;
}

void Plant::Consumed()
{
    simMap[m_location.y][m_location.x] = ' ';
    m_grown = false;
    m_timer = 0;
}

bool Plant::GetStatus()
{
    return m_grown;
}

void Plant::Grow()                                      // Evaluate growth status, then regrow based on timer and m_growtho
{
    if(m_grown == true)
    {
        return;
    }
    else
    {
        if(m_timer != m_growthCo)
        {
            m_timer++;
        }
        else
        {
            if(simMap[m_location.y][m_location.x] == ' ')
            {
                simMap[m_location.y][m_location.x] = m_id;
                m_timer = 0;
            }
        }
    }

    
}

void Plant::PrintDetails()
{
    cout << "Species: " << m_species << '\n';
    cout << "ID: " << m_id << '\n';
    cout << "Energy Points: " << m_energyPoints << '\n';
    cout << "Growth Coefficient: " << m_growthCo << '\n';
    cout << "Location(x,y): " << '(' << m_location.x << ',' << m_location.y << ')' << '\n';
}

void Plant::Tick()
{
    Grow();
}