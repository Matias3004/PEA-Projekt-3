#include "../inc/Graph.hh"

Graph::Graph() {}

Graph::~Graph()
{
    deleteMatrix();
}

void Graph::createMatrix()
{
    matrixPtr = new int *[vertexCount];
    for (int i = 0; i < vertexCount; i++)
    {
        matrixPtr[i] = new int[vertexCount];
        for (int j = 0; j < vertexCount; j++)
            matrixPtr[i][j] = INT32_MAX; // Maksymalna wartość int jako nieistniejąca krawędź
    }
}

void Graph::deleteMatrix()
{
    if (matrixPtr != nullptr)
    {
        for (int i = 0; i < vertexCount; i++)
            delete[] matrixPtr[i];

        delete[] matrixPtr;
        matrixPtr = nullptr;
    }
}

int Graph::readGraph(std::string filename)
{
    deleteMatrix();

    std::ifstream input(filename.c_str());
    if (!input)
        return 0;

    input >> vertexCount;

    createMatrix();

    for (int i = 0; i < vertexCount; i++)
    {
        for (int j = 0; j < vertexCount; j++)
        {
            int temp;
            input >> temp;
            matrixPtr[i][j] = temp;
            if (i == j)
                matrixPtr[i][j] = INT32_MAX;
        }
    }

    input.close();

    return 1;
}

std::string Graph::printStruct()
{
    if (matrixPtr == nullptr)
        return "Graf jest pusty!\n";

    std::string structure = "Macierz sąsiedztwa:\n\\";
    for (int i = 0; i < vertexCount; i++)
        structure += ' ' + to_string(i);

    structure += '\n';

    for (int i = 0; i < vertexCount; i++)
    {
        structure += to_string(i);
        for (int j = 0; j < vertexCount; j++)
        {
            if (matrixPtr[i][j] == INT32_MAX)
                structure += " x";
            else
                structure += ' ' + to_string(matrixPtr[i][j]);
        }
        structure += '\n';
    }

    return structure;
}

int Graph::getVertexCount()
{
    return vertexCount;
}

int Graph::getElement(int n, int m)
{
    return matrixPtr[n][m];
}

int** Graph::getMatrixPtr()
{
    return matrixPtr;
}

bool Graph::isEmpty()
{
    if (matrixPtr == nullptr)
        return true;
    else 
        return false;
}