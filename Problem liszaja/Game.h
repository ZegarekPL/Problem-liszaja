#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include <SFML/Window.hpp>
#include "Duration.h"
#include "Menu.h"

class Game {
public:
    int run(); 
    void drawEndAllHealth(sf::RenderWindow& window);
    void drawEndAllInfected(sf::RenderWindow& window);
private:
    Duration* duration;
    Board* board;
    Menu* menu;
    sf::Clock clock;
    float deltaTime;
    float allTime;
    void delay(int time, sf::RenderWindow& window, bool& menuOpen);
    bool isFirst = true;
    sf::Font font;
    sf::Text exitHealth;
    sf::Text exitInfected;
};
