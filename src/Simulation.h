#ifndef SIMULATION_H
#define SIMULATION_H
#include <vector>
#include <unordered_map>
#include "Organism.h"

// Variables.

extern vector<vector<char>> simMap;
extern vector<Organism*> simOrganisms;
extern unordered_map<char, vector<string>> bestiary;       // ID : Type, ID, eMax // Type, ID, growco, energy

extern int rows;
extern int cols;
// Functions.

void MakeBestiary(vector<string> species);
void MakeOrganisms(char c, Location eLocation);
void ReadSpecies(ifstream& input);
void InitializeMap(ifstream& input);
void LoadOrganisms();
Organism* SearchOrgs(Location lctn);
string CheckOrgType(Organism* org);
void PrintMap();
void SimStep(int steps = 1);
#endif