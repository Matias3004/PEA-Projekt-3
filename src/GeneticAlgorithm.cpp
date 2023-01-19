#include "../inc/GeneticAlgorithm.hh"

#include <vector>
#include <random>

// Inicjalizuje najkrotszą ściezkę metodą zachłanną startując z korzenia
void GeneticAlgorithm::initPath()
{
    if (shortestPath != nullptr)
        delete shortestPath;

    shortestPath = new int[cities.getVertexCount()];
    shortestPath[0] = startingVertex;

    bool *alreadyVisited = new bool[cities.getVertexCount()];
    for (int i = 0; i < cities.getVertexCount(); i++)
        alreadyVisited[i] = false;

    alreadyVisited[startingVertex] = true;

    for (int i = 0; i < cities.getVertexCount(); i++)
    {
        int min = INT_MAX;
        int chosen = -1;

        for (int j = 0; j < cities.getVertexCount(); j++)
        {
            if (cities.getElement(shortestPath[i], j) < min && !alreadyVisited[j])
            {
                min = cities.getElement(shortestPath[i], j);
                chosen = j;
            }
        }

        alreadyVisited[chosen] = true;
        shortestPath[i + 1] = chosen;
    }

    delete[] alreadyVisited;
    shortestPathValue = calculatePathLength(shortestPath);
}

// Oblicza długość danej ściezki
int GeneticAlgorithm::calculatePathLength(int *path)
{
    int length = 0;
    for (int i = 0; i < cities.getVertexCount(); i++)
    {
        length += cities.getElement(
            path[i], path[i + 1 >= cities.getVertexCount() ? 0 : i + 1]);
    }

    return length;
}

// Ustawia losową ściezkę na danym wskazniku
void GeneticAlgorithm::setRandomPath(int *path)
{
    std::vector<int> possibleCities;
    for (int i = 0; i < cities.getVertexCount(); i++)
        possibleCities.push_back(i);

    possibleCities.erase(possibleCities.begin() + startingVertex);
    path[0] = startingVertex;

    for (int i = 1; possibleCities.size() > 0; i++)
    {
        int randomNum = std::uniform_int_distribution<
            std::mt19937::result_type>{0, possibleCities.size() - 1}(rng);
        path[i] = possibleCities[randomNum];
        possibleCities.erase(possibleCities.begin() + randomNum);
    }
}

// Zwraca klasę danej ściezki -> im wyzsza, tym lepsza ściezka
int GeneticAlgorithm::gradePath(int *path)
{
    return shortestPathValue - calculatePathLength(path);
}

// Normalizuje klasy ściezek, aby były większe niz 0
void GeneticAlgorithm::normalizeGrades(int *grades, int populationSize)
{
    int min = 0;
    
    for (int i = 0; i < populationSize; i++)
    {
        if (grades[i] < min)
            min = grades[i];
    }

    min *= -1;
    min++;

    for (int i = 0; i < populationSize; i++)
        grades[i] += min;
}

// Kopiuje populację do innej na podstawie wybranych rodzicow
void GeneticAlgorithm::copyPopulation(int **from, int **to, int *selectedParents, int populationSize)
{
    for (int i = 0; i < populationSize; i++)
    {
        for (int j = 0; j < cities.getVertexCount(); j++)
            to[i][j] = from[selectedParents[i]][j];
    }
}

// Kopiuje niezmienioną populację do innej
void GeneticAlgorithm::copyPopulationIntact(int **from, int **to, int populationSize)
{
    for (int i = 0; i < populationSize; i++)
    {
        for (int j = 0; j < cities.getVertexCount(); j++)
            to[i][j] = from[i][j];
    }
}

// Wybiera rodzicow do selekcji na podstawie ruletki z uzyciem klas sciezek
void GeneticAlgorithm::selectByRoulette(int *grades, int *selection, int populationSize)
{
    int gradesSum = 0;

    for (int i = 0; i < populationSize; i++)
    {
        gradesSum += grades[i];
        grades[i] = gradesSum;
    }

    std::uniform_int_distribution<std::mt19937::result_type> rulDist(1, gradesSum - 1);

    for (int i = 0; i < populationSize; i++)
    {
        int selected = rulDist(rng);
        for (int j = 0; j < populationSize; j++)
        {
            if (selected - grades[j] < 0)
            {
                selection[i] = j;

                break;
            }
        }
    }
}

// Mutuje daną ściezkę zamieniając miejscami dwa rozne punkty
void GeneticAlgorithm::mutate(int *path)
{
    int pointA = 0;
    int pointB = 0;
    std::uniform_int_distribution<std::mt19937::result_type> popDist(
        0, cities.getVertexCount() - 1);

    while (pointA == pointB)
    {
        pointA = popDist(rng);
        pointB = popDist(rng);
    }

    swapElements(path, pointA, pointB);
}

// Zamienia miejscami dwa elementy
void GeneticAlgorithm::swapElements(int *path, int i, int j)
{
    int temp = path[i];
    path[i] = path[j];
    path[j] = temp;
}