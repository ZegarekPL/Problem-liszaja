#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
using namespace std;

class Board {
public:
    Board(unsigned int size);

    void draw(sf::RenderWindow& window);
    void handleClick(sf::RenderWindow& window);
    void highlightCell(unsigned int row, unsigned int col, sf::RenderWindow& window);

private:
    unsigned int size;
    std::vector<std::vector<sf::Color>> colors; // Dodaj to pole do klasy
};
