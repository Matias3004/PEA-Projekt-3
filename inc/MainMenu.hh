#pragma once
#include <string>
#include "Graph.hh"
#include "StringUtils.hh"

class MainMenu
{
    private:
        StringUtils su;

        std::string menu = "";
        std::string file;
        Graph graph;
        int time = 0;
        int population = 0;
        float crossesCoeff = 0;
        float mutationCoeff = 0;
        std::string crossoverType = "";

    public:
        MainMenu();
        ~MainMenu();

        void enable();
};