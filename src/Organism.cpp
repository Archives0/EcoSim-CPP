#include <iostream>
#include "Organism.h"
#include "Simulation.h"
using namespace std;

Organism::Organism(char species, char ID, Location location)
: m_species{species}, m_id{ID}, m_location{location}
{}

char Organism::GetID()
{
    return m_id;
}

void Organism::SetID(char ID)
{
    m_id = ID;
}

Location Organism::GetLocation()
{
    return m_location;
}

void Organism::SetLocation(int x, int y)
{
    m_location.x = x;
    m_location.y = y;
}

void Organism::PrintDetails()
{
    cout << "Species: " << m_species << '\n';
    cout << "ID: " << m_id << '\n';
    cout << "Location(x,y): " << '(' << m_location.x << ',' << m_location.y << ')' << '\n';
}

void Organism::Death()                              // Removes organism from simulation.
{
    simMap[m_location.y][m_location.x] = ' ';
    m_id = ' ';
    m_dead = true;
}

void Organism::Consumed()
{
    Death();
}

void Organism::Tick()
{
    cout << "No defined tick behavior for organism \n";
}