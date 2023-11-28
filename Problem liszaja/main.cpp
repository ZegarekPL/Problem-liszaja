#include <SFML/Graphics.hpp>
#include "Board.h"
#include <iostream>
using namespace std;

int main()
{

    unsigned int boardSize;

    do {
        cout << "Wpisz liczbe pol x: ";
        cin >> boardSize;

        if (boardSize > 11) {
            cout << "Error: Too large area!!! Try again." << endl;
        }
    } while (boardSize > 11);

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!", sf::Style::Titlebar | sf::Style::Close);

    Board board(boardSize);
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

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
            }
        }

        window.clear();
        board.draw(window);
        window.display();
    }

    return 0;
}