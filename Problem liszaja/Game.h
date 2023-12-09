#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include <SFML/Window.hpp>
#include "Duration.h"
#include "Menu.h"

class Game {
public:
    int run();
private:
    Menu menu;
    Duration duration;
    Board board;
    sf::Clock clock;
    float deltaTime;
    float allTime;

};
