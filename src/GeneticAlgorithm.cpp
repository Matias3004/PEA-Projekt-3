#include "../inc/GeneticAlgorithm.hh"

#include <vector>
#include <random>

// Konstruktor - inicjalizuje generator liczb losowych
GeneticAlgorithm::GeneticAlgorithm()
{
    rng.seed(std::random_device()());
}

// Destruktor - usuwa najkrótszą ścieżkę
GeneticAlgorithm::~GeneticAlgorithm()
{
    if (shortestPath != nullptr)
        delete[] shortestPath;
}

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
        int min = INT32_MAX;
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
            std::mt19937::result_type>{0, (uint32_t) possibleCities.size() - 1}(rng);
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

// Mutuje daną ściezkę zamieniając miejscami dwa różne punkty
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

// Kzyżuje dwie populacje jednopunktowo - PMX
void GeneticAlgorithm::crossOnePoint(int *pathA, int *pathB)
{
    // Tworzy tymczasowe ścieżki
    int *tempPathA = new int[cities.getVertexCount()];
    int *tempPathB = new int[cities.getVertexCount()];
    copyPath(pathA, tempPathA);
    copyPath(pathB, tempPathB);

    // Tworzy punkt krzyżowania
    std::uniform_int_distribution<std::mt19937::result_type> dist(
        0, (cities.getVertexCount() - 1));
    int crossingPoint = dist(rng);

    // Krzyżowanie oparte na PMX
    for (int i = 0; i < crossingPoint; i++)
    {
        int position = findInArray(pathA, tempPathB[i]);
        pathA[position] = pathA[i];
        pathA[i] = tempPathB[i];
    }
    for (int i = 0; i < crossingPoint; i++)
    {
        int position = findInArray(pathB, tempPathA[i]);
        pathB[position] = pathB[i];
        pathB[i] = tempPathA[i];
    }

    delete[] tempPathA;
    delete[] tempPathB;
}

// Znajduje podaną liczbę w tablicy i zwraca jej pozycję
int GeneticAlgorithm::findInArray(int *array, int number)
{
    for (int i = 0; i < cities.getVertexCount(); i++)
    {
        if (array[i] == number)
            return i;
    }

    return -1;
}

// Kopiuje jedną ścieżkę do drugiej
void GeneticAlgorithm::copyPath(int *from, int *to)
{
    for (int i = 0; i < cities.getVertexCount(); i++)
        to[i] = from[i];
}

// Ustawia źródło macierzy sąsiedztwa zawierającej miasta i odległości pomiędzy nimi
int GeneticAlgorithm::setSource(std::string filename)
{
    return cities.readGraph(filename);
}

// Wyświetla macież sąsiedztwa zawierającą miasta i odległości pomiędzy nimi
std::string GeneticAlgorithm::printSource()
{
    return cities.printStruct();
}

// Wyświetla najkrótszą ścieżkę
std::string GeneticAlgorithm::getShortestPath()
{
    if (cities.isEmpty() || shortestPath == nullptr)
        return "Nie wczytano grafu!";

    std::string temp = "";
    for (int i = 0; i < cities.getVertexCount(); i++)
        temp += to_string(shortestPath[i]) + " -> ";

    temp += to_string(shortestPath[0]);

    return temp;
}

// Getter
int GeneticAlgorithm::getShortestPathValue()
{
    return shortestPathValue == INT32_MAX ? 0 : shortestPathValue;
}

// Algorytm Genetyczny TSP
void GeneticAlgorithm::solve(const int populationSize, const double crossProb, const double mutProb, int iterations)
{
    if (cities.isEmpty() || populationSize % 2 == 1)
        return;

    // Ustawia najkrótszą ścieżkę początkową za pomocą metody zachłannej
    initPath();

    if (iterations == -1)
        iterations = cities.getVertexCount() * cities.getVertexCount() * 2;

    // Inicjalizuje populację początkową
    int **population;
    population = new int*[populationSize];
    for (int i = 0; i < populationSize; i++)
    {
        population[i] = new int[cities.getVertexCount()];
        setRandomPath(population[i]);
    }
    int **newPopulation;
    for (int i = 0; i < populationSize; i++)
        newPopulation[i] = new int[cities.getVertexCount()];

    int *selectedParents = new int[populationSize];

    // Przyznaje ocenę każdemu przedstawicielowi populacji
    int *grades = new int[populationSize];
    for (int j = 0; j < populationSize; j++)
        grades[j] = gradePath(population[j]);

    normalizeGrades(grades, populationSize);

    // Ustawia obecne rozwiązanie jako najlepsze znane
    int bestGrade = INT32_MAX * (-1);
    int bestFromPop;
    for (int i = 0; i < populationSize; i++)
    {
        if (grades[i] > bestGrade)
        {
            bestGrade = grades[i];
            bestFromPop = i;
        }
    }
    copyPath(population[bestFromPop], shortestPath);
    shortestPathValue = calculatePathLength(population[bestFromPop]);

    // Rozkład prawdopodobieństwa krzyżowania oraz mutacji
    std::uniform_int_distribution<double> happeningProb(0.0, 1.0);

    // Kolejne iteracje algorytmu
    for (int i = 0; i < iterations; i++)
    {
        // Wybiera rodziców na podstawie ruletki
        selectByRoulette(grades, selectedParents, populationSize);

        // Tworzy nową populację na podstawie wybranych rodziców
        copyPopulation(population, newPopulation, selectedParents, populationSize);

        // Krzyżowanie
        for (int j = 0; j < populationSize; j++)
        {
            if (happeningProb(rng) <= crossProb)
                crossOnePoint(newPopulation[j * 2], newPopulation[(j * 2) + 1]);
        }
        // Mutacje
        for (int j = 0; j < populationSize; j++)
        {
            if (happeningProb(rng) <= mutProb)
                mutate(newPopulation[j]);
        }

        // Ocena nowej populacji
        for (int i = 0; i < populationSize; i++)
            grades[i] = gradePath(newPopulation[i]);

        normalizeGrades(grades, populationSize);

        // Kopiuje nową populację do istniejącej populacji
        copyPopulationIntact(newPopulation, population, populationSize);

        // Ustawia nowe najlepsze rozwiązanie jeżeli zostało znalezione
        bestGrade = INT32_MAX * (-1);
        bestFromPop;
        for (int i = 0; i < populationSize; i++)
        {
            if (grades[i] > bestGrade)
            {
                bestGrade = grades[i];
                bestFromPop = i;
            }
        }
        if (calculatePathLength(population[bestFromPop]) < shortestPathValue)
        {
            copyPath(population[bestFromPop], shortestPath);
            shortestPathValue = calculatePathLength(population[bestFromPop]);
            std::cout << i << " " << shortestPathValue << std::endl;
        }
    }

    // Usuwa oceny
    delete[] grades;

    // Usuwa populację
    for (int i = 0; i < populationSize; i++)
        delete[] population[i];

    delete[] population;

    for (int i = 0; i < populationSize; i++)
        delete[] newPopulation[i];

    delete[] newPopulation;
    delete[] selectedParents;
}