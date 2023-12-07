#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Window.hpp>

class Game {
public:
    int run();
    void delay(int time, Board* board, sf::RenderWindow& window);
private:

};
