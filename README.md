[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/CQ0jbgGv)

# Dependencies

To run this simulation, you will need [GNU Make 4.1.1](https://www.gnu.org/software/software.html) and [g++ (GCC) 13.2.1](https://gcc.gnu.org/). This simulation has not been tested on other versions of these software, and therefore may not work.

# Starting the Simulation

To begin the simulation, open the command line interface and navigate to your file installation directiory.
Navigate to the src directory and enter the command 'make'.
After compiling has completed, you can begin the simulation by running the ecosystem binary using the command './ecosystem'.
You must provide your input files as arguments to the binary or the simulation will not play. These arguments must be input in the order of map, then species list. Breaking this order will inhibit the simulation from creating the bestiary. To access the input files in the input folder, enter the following command:

'./ecosystem "../input/species.txt" "../input/map.txt"'

Alternatively, running the command 'make sample' will run the above command automatically.

The simulation will begin by reading input arguments and using this to construct the map and a species bestiary. It will then initialize the map with present species from the bestiary. Messages will be provided in the command line to indicate where the program is in this process, so that the user may identify possible input errors.


# Playing the Simulation

Upon loading, the simulation map will be presented and three options will be available:
* s - Single step through the simulation.
* b - Batch steps through the simulation.
* x - Exit simulation.

When stepping through the simulation, organisms will have a chance to take all the actions available to them.
Plants will grow if they have previously been consumed.
Animals will move and search for food while avoiding predators.

Note that animals can only see in the cardinal directions relative to their position, and will not react to organisms diagnol to their position.
