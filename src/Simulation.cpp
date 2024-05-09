#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Simulation.h"
#include "Plant.h"
#include "Herbivore.h"
#include "Omnivore.h"
using namespace std;

ifstream inMap;
ifstream inSpec;

vector<vector<char>> simMap;
vector<Organism*> simOrganisms;
unordered_map<char, vector<string>> bestiary;       // ID as key, full attributes as value.

int rows{};
int cols{};

void MakeBestiary(vector<string> species);
void MakeOrganisms(char c, Location eLocation);

void ReadSpecies(ifstream& input)
{
    cout << "Reading species file..." << '\n';

    // inSpec = ifstream{"../input/species.txt"};
    
    if(!input)
    {
        cerr << "Could not read species file. \n";
        return;
    }

    cout << "Adding species to bestiary..." << '\n';

    while(input)
    {
        string fullRow;
        string token;
        getline(input, fullRow);
        std::istringstream iss(fullRow);
        vector<string> tokens;                      // type, ID, energy / (growthCo, energy)

        while(iss >> token)
        {
            tokens.push_back(token);
        }

        if(tokens.size() > 0)                       // Avoid segmentation faults
            MakeBestiary(tokens);
    }

    cout << "Bestiary completed." << '\n';
    input.close();
}

void InitializeMap(ifstream& input)
{
    cout << "Reading map file..." << '\n';
    // inMap = ifstream{"../input/map.txt"};

    if(!input)
    {
        cerr << "Could not read map file. \n";
        return;
    }

    while(input)
    {
        string fullRow;
        vector<char> rowVec;
        getline(input, fullRow);

        for(int i = 0; i < fullRow.length(); i++)
        {
            rowVec.push_back(fullRow[i]);
        }

        if(rowVec.size() > 0)
        {
            simMap.push_back(rowVec);
        }
    }
    cout << "Map read successfully." << '\n';
}

void LoadOrganisms()
{
    for(int i = 0; i < simMap.size(); i++)              // Read map and create organism objects.
    {
        for(int j = 0; j < simMap[i].size(); j++)
        {
            if(simMap[i][j] != ' ')
            {
                Location mapLoc{j,i};
                MakeOrganisms(simMap[i][j], mapLoc);
            }
        }
    }
}

void MakeBestiary(vector<string> species)               // Adds org data to dictionary.
{
    bestiary.insert({species[1][0], species});
}

void MakeOrganisms(char c, Location eLocation)
{
    vector<string> orgData = bestiary.at(c);            // plant a 1 5, herbivore A 20

    if(orgData[0] == "plant")                           // Init object with data from bestiary.
    {
        Plant* org = new Plant{orgData[1][0], orgData[1][0], eLocation, stoi(orgData[2]), stoi(orgData[3])};
        simOrganisms.push_back(org);
    }
    else if(orgData[0] == "herbivore")
    {
        Herbivore* org = new Herbivore{orgData[1][0], orgData[1][0], eLocation, stoi(orgData[2])};
        simOrganisms.push_back(org);
    }
    else if(orgData[0] == "omnivore")
    {
        Omnivore* org = new Omnivore{orgData[1][0], orgData[1][0], eLocation, stoi(orgData[2])};
        simOrganisms.push_back(org);
    }
}

string CheckOrgType(Organism* org)                      // Returns string based on org type for checks.
{
    if(org != nullptr)
    {
        if(typeid(*org) == typeid(Plant))
            return "Plant";
        else if(typeid(*org) == typeid(Herbivore))
            return "Herbivore";
        else if(typeid(*org) == typeid(Omnivore))
            return "Omnivore";
        else
            return "None";
    }

    return "None";
}

void PrintBorder(char c)                                // Used in print map for aesthertic purposes.
{
    for(int i = 0; i < simMap.size() +2; i++)
    {
        cout << c;
    }
    cout << '\n';
}

void PrintMap()
{
    cout << "Map:" << '\n';
    PrintBorder('\\');
    for(int i = 0; i < simMap.size(); i++)
    {
        cout << '|';
        for(int j = 0; j < simMap[i].size(); j++)
        {
            cout << simMap[i][j];
        }
        cout << '|';
        cout << '\n';
    }
    PrintBorder('/');
}

void SimStep(int steps)                              // Calls Tick() on all organisms.
{
    int counter = 0;

    while(counter < steps)
    {
        for(int i = 0; i < simOrganisms.size(); i++)
        {
            simOrganisms[i]->Tick();
        }
        counter++;
    }

    PrintMap();
}