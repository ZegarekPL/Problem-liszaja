#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "Board.h"
#include "Duration.h"

class Menu{
public:
    Menu();
    void drawMenu(sf::RenderWindow& window);
    void drawButton(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, const std::function<void()>& onClick, const sf::Color& mainColor, const sf::Color& hoverColor);
    void increase(int howMuch, const std::string& variable);
    void decrease(int howMuch, const std::string& variable);
private:
    sf::Font font;
    sf::Text title;
    sf::Text sizeText;
    sf::Text buttonText;
    sf::Text holdprocessText;
    sf::Text infectionPercentText;
    sf::Text infectedToImmuneText;
    sf::Text immuneCooldownText;
    sf::Text exit;
    Board board;
    Duration duration;
};

