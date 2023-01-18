CC = clang++
CFLAGS = -Wall -Wextra -Wpedantic -g -std=c++14

all: PEA-Projekt3

start: PEA-Projekt3
	./PEA-Projekt3

PEA-Projekt3: bin bin/main.o bin/StringUtils.o bin/Graph.o bin/GeneticAlgorithm.o bin/MainMenu.o
	$(CC) $(CFLAGS) -o PEA-Projekt3 bin/main.o bin/StringUtils.o bin/Graph.o bin/GeneticAlgorithm.o bin/MainMenu.o

bin:
	mkdir bin

bin/main.o: src/main.cpp
	$(CC) -c $(CFLAGS) -o bin/main.o src/main.cpp

bin/StringUtils.o: src/StringUtils.cpp
	$(CC) -c $(CFLAGS) -o bin/StringUtils.o src/StringUtils.cpp

bin/Graph.o: src/Graph.cpp
	$(CC) -c $(CFLAGS) -o bin/Graph.o src/Graph.cpp

bin/GeneticAlgorithm.o: src/GeneticAlgorithm.cpp
	$(CC) -c $(CFLAGS) -o bin/GeneticAlgorithm.o src/GeneticAlgorithm.cpp

bin/MainMenu.o: src/MainMenu.cpp inc/MainMenu.hh
	$(CC) -c $(CFLAGS) -o bin/MainMenu.o src/MainMenu.cpp

clean:
	rm -rf *.o bin PEA-Projekt3