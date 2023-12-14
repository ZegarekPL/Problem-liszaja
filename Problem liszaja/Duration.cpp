#include "Duration.h"

Duration::Duration(int maxround, unsigned int holdprocess, int infectionPercent, unsigned int infectedToImmune, unsigned int immuneCooldown) {
    this->maxround = maxround;
    this->holdprocess = holdprocess;
    this->infectionPercent = infectionPercent;
    this->infectedToImmune = infectedToImmune;
    this->immuneCooldown = immuneCooldown;
}



void Duration::consoleStart() {
    /*
    * */
    do {
        std::cout << "Wpisz ilosc rund symulacji: ";
        std::cin >> maxround;

        if (maxround <= 0) {
            std::cout << "Error: Cant be less than 0 or 0." << std::endl;
        }
    } while (maxround <= 0);
    
    do {
        std::cout << "Wpisz czas miedzy krokami symulacji: ";
        std::cin >> holdprocess;

        if (holdprocess <= 0 || holdprocess > 60) {
            std::cout << "Error: Too much time for holdprocess." << std::endl;
        }

    } while (holdprocess <= 0 || holdprocess > 60);
    do {
        std::cout << "Wpisz szanse zarazenia (wpisuj¹c np. 0.8 = 80%): ";
        std::cin >> infectionPercent;

        if (infectionPercent < 0 || infectionPercent > 1) {
            std::cout << "Error: Too much percent of infection." << std::endl;
        }

    } while (infectionPercent < 0 || infectionPercent > 1);
    do {
        std::cout << "Wpisz po ilu rundach komorka zmienia status z Infected na Immune: ";
        std::cin >> infectedToImmune;

        if (infectedToImmune <= 0) {
            std::cout << "Error: Cant be less than 0." << std::endl;
        }

    } while (infectedToImmune <= 0);
    do {
        std::cout << "Wpisz po ilu rundach komorka pozostanie Immune: ";
        std::cin >> immuneCooldown;

        if (immuneCooldown <= 0) {
            std::cout << "Error: Cant be less than 0." << std::endl;
        }
    } while (immuneCooldown <= 0);
}