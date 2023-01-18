#include "../inc/MainMenu.hh"
#include "../inc/GeneticAlgorithm.hh"

#include <iostream>

MainMenu::MainMenu()
{
    menu.append("===========================================\n");
    menu.append("===============PEA PROJEKT 3===============\n");
    menu.append("===========================================\n");
    menu.append("\t1. Wczytaj graf\n");
    menu.append("\t2. Podaj czas\n");
    menu.append("\t3. Podaj liczność populacji\n");
    menu.append("\t4. Podaj wspołczynnik krzyzowania\n");
    menu.append("\t5. Podaj wspołczynnik mutacji\n");
    menu.append("\t6. Podaj typ krzyzowania\n");
    menu.append("\t7. Algorytm genetyczny\n");
    menu.append("\t8. Test automatyczny\n");
    menu.append("\t0. Zakończ program\n");
    menu.append("===========================================\n");
    menu.append("Twoj wybor: ");
}

MainMenu::~MainMenu() {}

void MainMenu::enable()
{
    int choice = 99;

    while (true)
    {
        std::cout << "Czas: " << time << "s\n";
        std::cout << "Populacja: " << population << std::endl;
        std::cout << "Wspołczynnik krzyzowania: " << crossesCoeff << std::endl;
        std::cout << "Wspolczynnik mutacji: " << mutationCoeff << std::endl;
        std::cout << "Typ krzyzowania: " << crossoverType << std::endl;
        std::cout << graph.getDescription();
        std::cout << menu;

        std::cin >> choice;

        switch (choice)
        {
            case 1:
            {
                do
                {
                    std::cout << "Podaj nazwę pliku: ";
                    std::cin >> file;
                } while (file == "");
                graph.readGraph(file);
                
                break;
            }
            case 2:
            {
                do
                {
                    std::cout << "Podaj czas [s]: ";
                    std::cin >> time;
                } while (!time);
                
                break;
            }
            case 3:
            {
                do
                {
                    std::cout << "Podaj liczność populacji: ";
                    std::cin >> population;
                } while (!population);
                
                break;
            }
            case 4:
            {
                do
                {
                    std::cout << "Podaj wspołczynnik krzyzowania: ";
                    std::cin >> crossesCoeff;
                } while (!crossesCoeff);
                
                break;
            }
            case 5:
            {
                do
                {
                    std::cout << "Podaj wspołczynnik mutacji: ";
                    std::cin >> mutationCoeff;
                } while (!mutationCoeff);
                
                break;
            }
            case 6:
            {
                do
                {
                    std::cout << "Podaj typ krzyzowania [OX/PMX]: ";
                    std::cin >> crossoverType;
                } while (crossoverType == "" ||
                    !(su.iequals(crossoverType, "OX") ||
                    su.iequals(crossoverType, "PMX")));

                crossoverType = su.toUpperCase(crossoverType);
                
                break;
            }
            case 7:
            {
                if (!time || !population || !crossesCoeff || !mutationCoeff)
                {
                    std::cout << "Nie podano wszystkich parametrow algorytmu";
                    std::cin.get();
                }
                else
                {
                    GeneticAlgorithm ga(&graph, time, population, crossesCoeff, mutationCoeff);
                    ga.apply(true);
                    std::cin.get();
                }

                break;
            }
            case 8:
            {
                if (!time || !population || !crossesCoeff || !mutationCoeff)
                {
                    std::cout << "Nie podano wszystkich parametrow algorytmu";
                    std::cin.get();
                }
                else
                {
                    std::string filename;
                    std::cout << "Podaj nazwę pliku do zapisania wyniku: ";
                    std::cin >> filename;

                    GeneticAlgorithm ga(&graph, time, population, crossesCoeff, mutationCoeff);
                    for (size_t i = 0; i < 100; ++i)
                    {
                        std::cout << std::endl << i + 1 << " pomiar...\n";
                        ga.apply(true);
                    }

                    std::cout << "\nPomiary zakończone!" << std::endl;
                    std::cin.get();
                }

                break;
            }
            case 0:
                return;
        }

        std::cin.ignore();
        system("clear");
    }
}