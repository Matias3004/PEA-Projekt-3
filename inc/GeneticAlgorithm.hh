#pragma once

#include "Graph.hh"
#include <vector>

class GeneticAlgorithm
{
    private:
        unsigned long stop;
        int populationSize;
        float crossRate;
        float mutationRate;
        int **matrix;
        int size;

    public:
        GeneticAlgorithm(Graph*, int, int, float, float);

        void orderedCrossover(std::vector<int>&, std::vector<int>&);
        void partiallyCrossover(std::vector<int>&, std::vector<int>&);

        int calculatePath(std::vector<int>&);
        bool isInPath(int, int, int, std::vector<int>&);

        void saveResultsToFile(std::string, int, double);

        int apply(bool);
};