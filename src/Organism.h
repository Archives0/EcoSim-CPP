#ifndef ORGANISM_H
#define ORGANISM_H
#include <iostream>
using namespace std;

struct Location                                         // Locations begin at index 0.
{
    int x{};
    int y{};
};

class Organism
{
    protected:
    char m_species{};
    char m_id{};
    bool m_dead{};
    // char m_screenID{m_id};
    Location m_location{};
    void Death();

    public:
    Organism(char species, char ID, Location location);
    virtual void Consumed();
    // void TickEvent();
    char GetID();
    void SetID(char ID);
    Location GetLocation();
    void SetLocation(int x, int y);
    virtual void PrintDetails();
    virtual void Tick();
};
#endif