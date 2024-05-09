all: ecosystem.bin

ecosystem.bin: Main.o Simulation.o Organism.o Plant.o Animal.o Herbivore.o Omnivore.o
	g++ $^ -o $@

Main.o: Main.cpp Simulation.o
	g++ -c Main.cpp

Simulation.o: Simulation.cpp Organism.o Plant.o Animal.o Herbivore.o Omnivore.o
	g++ -c Simulation.cpp

Omnivore.o: Omnivore.h Omnivore.cpp Animal.h Organism.h
	g++ -c Omnivore.cpp

Herbivore.o: Herbivore.h Herbivore.cpp Animal.h Organism.h
	g++ -c Herbivore.cpp

Animal.o: Animal.h Animal.cpp Organism.h
	g++ -c Animal.cpp

Plant.o: Plant.h Plant.cpp Organism.h
	g++ -c Plant.cpp

Organism.o: Organism.h Organism.cpp
	g++ -c Organism.cpp

clean:
	rm -rf *.bin *.o *.gch

sample:
	./ecosystem.bin "../input/map.txt" "../input/species.txt"
