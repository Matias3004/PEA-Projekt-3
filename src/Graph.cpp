#include "../inc/Graph.hh"

#include <fstream>
#include <string>
#include <iostream>

Graph::Graph() {}

Graph::~Graph() {}

bool Graph::readGraph(std::string filename)
{
    int **temp;
    description = "";
    std::string tempDesc = "";

    std::ifstream fin;
    fin.open(filename);

    if (fin.fail() || fin.eof())
        return false;

    if (vertexCount)
    {
        for (int i = 0; i < vertexCount; i++)
            delete[] matrix[i];

        delete[] matrix;
    }

    for (int i = 0; i < 3; i++)
    {
        getline(fin, tempDesc);
        description.append(tempDesc + "\n");
    }

    fin >> tempDesc;

    description.append(tempDesc + "\n");
    fin >> vertexCount;

    description.append (std::to_string(vertexCount) + "\n");

    for (int i = 0; i < 4; i++)
        getline(fin, tempDesc);

    temp = new int *[vertexCount];

    for (int i = 0; i < vertexCount; i++)
        temp[i] = new int[vertexCount];

    for (int c = 0; c < vertexCount; c++)
    {
        for (int r = 0; r < vertexCount; r++)
            fin >> temp[r][c];
    }

    fin.close();

    matrix = temp;

    return true;
}

bool Graph::readGraphSmall(std::string filename)
{
    int **temp;

    std::ifstream fin;
    fin.open(filename);

    if (fin.fail() || fin.eof())
        return false;

    if (vertexCount)
    {
        for (int i = 0; i < vertexCount; i++)
            delete[] matrix[i];

        delete[] matrix;
    }

    fin >> vertexCount;

    temp = new int *[vertexCount];

    for (int i = 0; i < vertexCount; i++)
        temp[i] = new int[vertexCount];

    for (int c = 0; c < vertexCount; c++)
    {
        for (int r = 0; r < vertexCount; r++)
            fin >> temp[r][c];
    }

    fin.close();

    matrix = temp;

    return true;
}

int** Graph::getMatrix()
{
    return matrix;
}

int Graph::getVertexCount()
{
    return vertexCount;
}

std::string Graph::getDescription()
{
    if (!vertexCount)
        return "Brak danych\n";
    else
        return description;
}

std::string Graph::toString()
{
    std::string graph = "";
    graph.append(description);

    if (vertexCount)
    {
        for (int r = 0; r < vertexCount; r++)
        {
            for (int c = 0; c < vertexCount; c++)
            {
                if ((matrix[r][c] < 10) && (matrix[r][c] >= 0))
                    graph += std::to_string(matrix[r][c]) + "    ";
                else if (((matrix[r][c] < 100) && (matrix[r][c] > 9)) || (matrix[r][c] < 0))
                    graph += std::to_string(matrix[r][c]) + "   ";
                else if (matrix[r][c] == 100000000)
                    graph += "N    ";
                else
                    graph += std::to_string(matrix[r][c]) + "  ";
            }
            graph += "\n";
        }
    }
    else
        graph = "Graf pusty\n";

    return graph;
}