#include <SFML/Graphics.hpp>
#include "Board.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

void delay(int time, Board* board, RenderWindow& window) {
    Clock delayClock;
    delayClock.restart();
    time *= 1000;
    while (delayClock.getElapsedTime().asMilliseconds() < time) {
        board->draw(window);
    }
}

int main()
{
    unsigned int boardSize;
    float maxround;
    unsigned int holdprocess;
    float infectionPercent;
    unsigned int infectedToImmune;
    unsigned int immuneCooldown;
    do {
        std::cout << "Wpisz liczbe pol x: ";
        std::cin >> boardSize;

        if (boardSize <= 0 || boardSize > 11) {
            std::cout << "Error: Too large area!!! Try again." << std::endl;
        }
    } while (boardSize <= 0 || boardSize > 11);
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
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Problem liszaja", sf::Style::Titlebar | sf::Style::Close);

    Board board(boardSize);

    sf::Clock clock;
    bool gameStarted = false;  // Dodaj zmienn¹ kontroluj¹c¹, czy gra zosta³a rozpoczêta
    int currentround = 1;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Obs³uga klikniêcia mysz¹
            
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (!gameStarted) {
                    gameStarted = true;  // Rozpocznij grê po pierwszym klikniêciu myszy
                }
                // Zalicz klikniêcie tylko w pierwszej rundzie
                if (currentround == 1) {
                    window.clear();
                    board.handleClick(currentround, window);
                    board.draw(window);
                    window.display();
                    cout << "All: " << boardSize * boardSize << endl;
                    currentround = 2;
                }
            }

            // Rozpocznij pêtlê tylko jeœli gra zosta³a ju¿ uruchomiona

            if (currentround != 1 && currentround <= maxround) {
                for (currentround = 2; currentround <= maxround; currentround++) {
                    float deltaTime = clock.restart().asSeconds();
                    delay(holdprocess, &board, window);
                    board.update(boardSize, currentround, deltaTime, window, infectionPercent, infectedToImmune, immuneCooldown);
                    window.clear();
                    board.draw(window);
                    window.display();
                }
            }
        }
        window.clear();
        board.draw(window);
        window.display();
    }

    return 0;
}
