#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
class Board;
class Duration;

class Menu{
public:
    void drawMenu(sf::RenderWindow& window);
    void drawButton(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, const std::function<void()>& onClick, const sf::Color& mainColor, const sf::Color& hoverColor);
    void increase(int howMuch, const std::string& variable);
    void decrease(int howMuch, const std::string& variable);
    void increaseFloat(float howMuch, const std::string& variable);
    void decreaseFloat(float howMuch, const std::string& variable);
    int menuSize=50;
    int menuMaxround = 1000;
    float menuHoldprocess = 0.5;
    int menuInfectionPercent = 50;
    int menuInfectedToImmune = 1;
    int menuImmuneCooldown = 1;
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
    Board* board;
    Duration* duration;
};

