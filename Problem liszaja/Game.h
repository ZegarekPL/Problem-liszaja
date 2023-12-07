#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Window.hpp>
#include "Duration.h"

class Game {
public:
    int run();
private:
    Duration duration;
    sf::Clock clock;
};
