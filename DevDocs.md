# Developer Documentation

This documentation is meant for developers who intend to modify, extend, learn from, or simply examine this simulation on a technical level. User documentation can be found in the [README](README.md) for this repository.

# Organisms

All organisms within the simulation inheret from the base 'Organism' class. The organism class stores information that is common for all animals and is used in various calculations throughout the simulation. These components are as follows:

* m_species - The species of the organism. More information in File Input section.
* m_id - The screen identifier for the organism.
* m_location - A unique data structure which is used to specify the organism's location on the map.

In addition to these components, the Organism class also contains functions which are inhereted by all organisms:

* GetID / SetID - Used to retrieve and update the value of m_id, respectively.
* GetLocation / SetLocation - Used to retrieve and update an organism's location, respectively.
* PrintDetails - Used to print the current values of the organism's member variables.
* Tick - Called once for each simulation step. Contains all the actions the organism will perform for each step.

## Plant

Plant is the first class derived from the Organism class. Plants do not have the ability to move and possess components not present in the parent class.

* m_growthCo - Plant growth coefficient. Determines the amount of time a plant will remain unavailable after being consumed.
* m_energyPoints - The amount of energy points provided to the animal which consumes the plant.
* m_timer - An internal timer used for calculating plant regrowth.
* m_grown - Boolean value indicating the plant's growth state.

In addition to these components, plants contain specialized functions not present in the organism class:

* GetStatus - Returns true if the plant is fully grown. Returns false if not.
* GetEnergy - Returns the amount of energy stored in the plant.
* Grow - Called every simulation step. Uses m_growthCo to calculate plant regrowth.

## Animal

The animal class derives from the organism class, similar to the plant class. Animals possess a range of abilities not present in plants, as well as their own set of specialized components. These components are as follows:

* m_maxEnergy - The maximum amount of energy an animal can store.
* m_currentEnergy - The amount of energy the animal currently has. Used for checking if an animal can move.
* m_dead - Check if an animal is alive or dead.

The animal class also possesses a host of specialized functions:

* Edible - Checks if the input organism can be consumed by the animal.
* Death - Changes the animal m_id to blank and changes m_dead to true. Effectively removes animal from simulation.
* GetStatus - Returns the value of m_dead.
* GetCurrentEnergy - Retrieves the amount of energy the animal currently possesses.
* SearchOrgs - Used to identify an organism based on its location in the simulation map.
* Consume - Basic logic for consuming another organism. Virtual function that is further derived in kater classes.
* CheckForPredators - Checks local vicinity for predator animals. Returns direction guiding the animal away from the perdator.
* CheckForFood - Similar to CheckForPredators, but guides the animal towards food if it is edible.
* CheckSurroundings - Processes predator check and food check, then combines their direction for a net movement direction.
* Move - Changes the animal position based on CheckSurroundings calculation. Moves randomly if no entities in vicinity.

The animal class also utilizes the libraries ctime and cstdlib together to randomly generate numbers used for navigation.

### Herbivore

The herbivore class derives from the Animal class and possesses many of the same behaviors. In fact, it is nearly identical to the Animal class, but is distinctly different from the omnivore class.

### Omnivore

The omnivore class derives from the animal class, and possesses many of the same behaviors. Unlike herbivores or base animals, the omnivore is allowed to consume both animals and plants. This is done by adding an additional check to the Edible function that allows the function to evaluate to true if it detects the edible conditions on another animal.

# Simulation

The second major component to the operation of the simulation in the simulation script. This script contains functions that allow for file input, map rendering, and general simulation operations. The simulation makes use of the following libraries for the following reasons.

* iostream - Handling simulation input and output.
* fstream - Handling user file input.
* sstream - Used for tokenizing file input for bestiary definition.
* string - Used for converting string data to integer data for organism construction.
* unordered_map - Used for storing species data in bestiary.
* vector - Used for storing map in 2D vector field. Also used for storing organisms in the simulation scene

The simulation script also incorporates the header files of the different derived organism types to perform particular operations that involve components stored within these organism classes.

* ReadSpecies - Parses species input file and tokenizes data to store in bestiary.
* InitializeMap - Reads map input file and defines organisms if they are present in the bestiary.
* MakeOrganisms - Defines an organism class based on input when parsing map file.
* MakeBestiary - Stores information on organisms specified in the species input file.
* CheckOrgType - Returns a string value based on the organism type stored in the bestiary.
* PrintMap - Iterates across the simMap 2D vector and prints the current state of the map.
* SimStep - Iterates across the list of organisms present in the simulation and calls their tick function.