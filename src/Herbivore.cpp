#include <iostream>
#include "Animal.h"
#include "Herbivore.h"
using namespace std;

void Herbivore::Tick()
{
    if(!m_dead)
    {
        Location moveDir = CheckSurroundings();
        Move(moveDir);
        Consume();
    }
}