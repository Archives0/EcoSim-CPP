#include <iostream>
#include <fstream>
#include "Simulation.h"
using namespace std;

void Menu();
void BatchStep();
void PrintAllDetails();

int main(int argc, char* argv[])
{
    cout << "Starting Simulation \n";
    ifstream inMap(argv[1]);
    ifstream inspec(argv[2]);

    InitializeMap(inMap);
    ReadSpecies(inspec);
    LoadOrganisms();
    //PrintAllDetails();
    PrintMap();
    Menu();
}

void Menu()
{
    char input{};

    while(input != 'x')
    {
        cout << "Enter s to step. Enter b to batch steps. Enter x to quit: ";
        cin >> input;
        cout << '\n';

        if(input != 's' && input != 'x' && input != 'b')
        {
            cerr << "Input not recognized. \n";
        }
        else if(input == 's')
        {
            SimStep(1);
        }
        else if(input == 'b')
        {
            BatchStep();
        }
    }
}

void BatchStep()
{
    int steps{};
    cout << "Enter desired number of sim steps: ";
    cin >> steps;
    cout << '\n';

    if(steps < 0)
    {
        cerr << "Cannot process negative steps. Try again. \n";
        return;
    }
    else if(steps == 0)
    {
        cout << "Zero steps selected. Returning to menu. \n";
        return;
    }
    else
    {
        SimStep(steps);
    }
}

void PrintAllDetails()
{
    for(int i = 0; i < simOrganisms.size(); i++)
    {
        simOrganisms[i]->PrintDetails();
    }
}