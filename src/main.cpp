#include "../inc/GeneticAlgorithm.hh"

#include <iostream>
#include <chrono>


void displayMenu()
{
    std::cout << "===========================================\n";
    std::cout << "===============PEA PROJEKT 3===============\n";
    std::cout << "===========================================\n";
    std::cout << "\t1. Wczytaj graf\n";
    std::cout << "\t2. Algorytm Genetyczny\n";
    std::cout << "\t3. Wyświetl graf\n";
    std::cout << "\t4. Pomiary automatyczne\n";
    std::cout << "\t0. Wyjście\n";
    std::cout << "Twój wybór: ";
}

void waitForConfirmation()
{
    std::cout << "Naciśnij dowolny klawisz aby kontynuować" << std::endl;
    std::cin.clear();
    std::cin.ignore(256, '\n');
    getchar();
}

std::string testDataFolder = "Test Files/";
std::ofstream testOutput;
std::string testFileOutput = testDataFolder + "testsData.csv";

const int mutationChancesCount = 4;
const double mutationChances[mutationChancesCount] = { 0.01, 0.05, 0.1, 0.15};
const int crossChancesCount = 6;
const double crossChances[crossChancesCount] = { 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };
const int populationSizeCount = 4;
const int populationSize[populationSizeCount] = { 10, 30, 50, 70};
const int testsCount = 20;

int main()
{
    char opt;
    std::string filename;
    GeneticAlgorithm testGA;

    while (true)
    {
        system("clear");
        displayMenu();
        opt = getchar();
        system("clear");
        switch (opt)
        {
            case '1':
            {
                std::cout << "Podaj nazwę pliku: ";
                std::cin >> filename;
                if (!testGA.setSource(testDataFolder + filename))
                {
                    std::cout << "Błąd podczas wczytywania pliku!" << std::endl;
                    waitForConfirmation();

                    break;
                }

                std::cout << "Dane wczytane pomyślnie!" << std::endl;
                waitForConfirmation();

                break;
            }
            case '2':
            {
                int pop, iter;
                double crossCh, mutCh;

                std::cout << "Podaj liczność populacji: ";
                std::cin >> pop;

                std::cout << "Podaj liczbę iteracji: ";
                std::cin >> iter;

                std::cout << "Podaj współczynnik krzyżowania: ";
                std::cin >> crossCh;

                std::cout << "Podaj współczynnik prawdopodobieństwa mutacji: ";
                std::cin >> mutCh;

                testGA.solve(pop, crossCh, mutCh, iter);

                std::cout << "Znaleziona ścieżka:\n";
                std::cout << testGA.getShortestPath() << std::endl;
                std::cout << "Koszt: ";
                std::cout << testGA.getShortestPathValue() << std::endl;

                waitForConfirmation();

                break;
            }
            case '3':
            {
                std::cout << testGA.printSource() << std::endl;

                waitForConfirmation();

                break;
            }
            case '4':
            {
                testOutput.open(testFileOutput);
                if (!testOutput)
                {
                    std::cout << "Błąd otwarcia pliku do zapisu wyników testów!";
                    waitForConfirmation();

                    break;
                }

                testOutput << "Czasy podane w mikrosekundach" << std::endl;

                testOutput << "Algorytm Genetyczny" << std::endl;
            }
        }
    }
}