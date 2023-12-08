#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include <SFML/Window.hpp>
#include "Duration.h"

class Game {
public:
    int run();
private:
    Duration duration;
    Board board;
    sf::Clock clock;

};
