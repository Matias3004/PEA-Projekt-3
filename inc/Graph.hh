#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifndef TO_STRING // TO_STRING
#define TO_STRING // TO_STRING
template<class s>
std::string to_string(s data)
{
    std::stringstream ss;
    ss << data;

    return ss.str();
}
#endif //

class Graph
{
    private:
        int **matrixPtr = nullptr;
        int vertexCount = 0;

        void createMatrix();
        void deleteMatrix();

    public:
        Graph();
        ~Graph();

        int readGraph(std::string);
        std::string printStruct();
        int getVertexCount();
        int getElement(int, int);
        int** getMatrixPtr();
        bool isEmpty();
};