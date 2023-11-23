#pragma once
#include <SFML/Graphics.hpp>

class Board {
public:
    Board(unsigned int size);
    void draw(sf::RenderWindow& window);

private:
    unsigned int size;
};

