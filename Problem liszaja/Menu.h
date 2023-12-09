#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "Board.h"
#include "Duration.h"

class Menu{
public:
    Menu();
    void delay(int time, sf::RenderWindow& window);
    void consoleStart();
    void drawMenu(sf::RenderWindow& window);
    void drawButton(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, const std::function<void()>& onClick);
    void increase(int howMuch);
    void decrease(int howMuch);
private:
    sf::Font font;
    sf::Text title;
    sf::Text sizeText;
    sf::Text buttonText;
    sf::Text holdprocessText;
    sf::Text infectionPercentText;
    sf::Text infectedToImmuneText;
    sf::Text immuneCooldownText;
    Board board;
    Duration duration;
};

