#pragma once

#include "Graph.hh"

#include <random>

class GeneticAlgorithm
{
    private:
        Graph cities;
        int* shortestPath = nullptr;
        int shortestPathValue = INT_MAX;
        int startingVertex = 0;
        std::mt19937 rng;

        void initPath();
        int calculatePathLength(int*);
        void setRandomPath(int*);
        int gradePath(int*);

        void normalizeGrades(int*, int);
        void copyPopulation(int**, int**, int*, int);
        void copyPopulationIntact(int**, int**, int);
        void selectByRoulette(int*, int*, int);

        void mutate(int*);

        void swapElements(int*, int, int);
        void crossOnePoint(int*, int*);
        int findInArray(int*, int);
        void copyRoute(int*, int*);

    public:
        GeneticAlgorithm();
        ~GeneticAlgorithm();

        int setSource(std::string);
        std::string printSource();
        std::string getShortestPath();
        int getShortestPathValue();

        void solve(const int, const double, const double, int, const int);
};