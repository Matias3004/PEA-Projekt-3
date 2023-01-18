#pragma once

#include <string>

class Graph
{
    private:
        int **matrix = nullptr;
        int vertexCount = 0;
        std::string description = "";

    public:
        Graph();
        ~Graph();

        bool readGraph(std::string);
        bool readGraphSmall(std::string);

        int** getMatrix();
        int getVertexCount();
        std::string getDescription();

        std::string toString();
};