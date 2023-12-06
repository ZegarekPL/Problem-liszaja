#include <SFML/Graphics.hpp>
#include "Board.h"
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    unsigned int boardSize;
    float maxround;
    unsigned int holdprocess;
    do {
        std::cout << "Wpisz liczbe pol x: ";
        std::cin >> boardSize;

        if (boardSize > 11) {
            std::cout << "Error: Too large area!!! Try again." << std::endl;
        }
        do {
            std::cout << "Wpisz ilosc rund symulacji: ";
            std::cin >> maxround;

            if (maxround <= 0) {
                std::cout << "Error: round." << std::endl;
            }
            do {
                std::cout << "Wpisz czas miedzy krokami symulacji: ";
                std::cin >> holdprocess;

                if (holdprocess > 600) {
                    std::cout << "Error: Too much time for holdprocess." << std::endl;
                }
            } while (holdprocess > 600);
        } while (maxround <= 0);
    } while (boardSize > 11);

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Problem liszaja", sf::Style::Titlebar | sf::Style::Close);

    Board board(boardSize);

    sf::Clock clock;
    bool gameStarted = false;  // Dodaj zmienn¹ kontroluj¹c¹, czy gra zosta³a rozpoczêta

    while (window.isOpen())
    {
        int currentround = 1;
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
                    board.handleClick(currentround, window);
                    currentround = 2;
                }
            }
        }

        // Rozpocznij pêtlê tylko jeœli gra zosta³a ju¿ uruchomiona
        if (currentround !=1 ) {
            for (currentround = 2; currentround <= maxround; currentround++) {
                float deltaTime = clock.restart().asSeconds();
                board.update(currentround, deltaTime, window);
                window.clear();
                board.draw(window);
                window.display();
                std::this_thread::sleep_for(std::chrono::seconds(holdprocess));
            }
        }
        window.clear();
        board.draw(window);
        window.display();
    }

    return 0;
}
