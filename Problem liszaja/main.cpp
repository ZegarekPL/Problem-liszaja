#include <SFML/Graphics.hpp>
#include "Board.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int main()
{
    unsigned int boardSize;
    float maxtimer;
    unsigned int holdprocess;
    do {
        cout << "Wpisz liczbe pol x: ";
        cin >> boardSize;

        if (boardSize > 11) {
            cout << "Error: Too large area!!! Try again." << endl;
        }
        do {
            cout << "Wpisz ilosc rund symulacji: ";
            cin >> maxtimer;

            if (maxtimer > 600) {
                cout << "Error: Too much time." << endl;
            }
            do {
                cout << "Wpisz czas miedzy krokami symulacji: ";
                cin >> holdprocess;

                if (holdprocess > 600) {
                    cout << "Error: Too much time for holdprocess." << endl;
                }
            } while (holdprocess > 600);
        } while (maxtimer > 600);
    } while (boardSize > 11);

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Problem liszaja", sf::Style::Titlebar | sf::Style::Close);

    Board board(boardSize);
    
    sf::Clock clock;  // Dodaj zegar do œledzenia czasu miêdzy klatkami

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Obs³uga klikniêcia mysz¹
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                board.handleClick(window);

                // Dodaj symulacjê automatu po klikniêciu mysz¹
                while (window.isOpen() && board.timer <= maxtimer* holdprocess) {
                    float deltaTime = clock.restart().asSeconds();
                    board.update(deltaTime, window);
                    window.clear();
                    board.draw(window);
                    window.display();
                    this_thread::sleep_for(std::chrono::seconds(holdprocess));
                }
            }
        }

        window.clear();
        board.draw(window);
        window.display();
    }

    return 0;
}
