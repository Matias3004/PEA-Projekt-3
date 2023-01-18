#pragma once
#include <string>
#include "Graph.hh"

class MainMenu
{
    private:
        std::string menu = "";
        std::string file = "";
        Graph graph;
        int time = 0;
        int population = 0;
        float crossesCoeff = 0;
        float mutationCoeff = 0;
        std::string crossoverType = "";

    public:
        MainMenu();
        ~MainMenu();

        bool iequals(const std::string&, const std::string&);
        std::string toUpperCase(std::string&);

        void enable();
};