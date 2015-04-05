# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=clang++ -std=c++11
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS=-c -Wall

all:	antColony

antColony:	main.o AntAlgorithm.o PheromoneMap.o Ant.o Problem.o City.o
	$(CC) main.o AntAlgorithm.o PheromoneMap.o Ant.o Problem.o City.o -o antColony

main.o:	main.cpp AntAlgorithm.h
	$(CC) $(CFLAGS) main.cpp

AntAlgorithm.o:	AntAlgorithm.cpp AntAlgorithm.h Problem.h City.h PheromoneMap.h Ant.h
	$(CC) $(CFLAGS) AntAlgorithm.cpp

PheromoneMap.o:	PheromoneMap.cpp PheromoneMap.h City.h
	$(CC) $(CFLAGS) PheromoneMap.cpp

Ant.o:	Ant.cpp Ant.h PheromoneMap.h City.h
	$(CC) $(CFLAGS) Ant.cpp

Problem.o:	Problem.cpp Problem.h City.h
	$(CC) $(CFLAGS) Problem.cpp

City.o:	City.cpp City.h
	$(CC) $(CFLAGS) City.cpp

clean:
	rm *o antColony