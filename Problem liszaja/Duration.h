#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

class Duration {
public:
	Duration();
	void delay(int time, sf::RenderWindow& window);
	void consoleStart();
    void drawMenu(sf::RenderWindow& window);
    void drawButton(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, const std::function<void()>& onClick);
    void increase();
    void decrease();
    int maxround;
    unsigned int holdprocess;
    float infectionPercent;
    unsigned int infectedToImmune;
    unsigned int immuneCooldown;
	
private:
	sf::Font font;
	sf::Text title;
    sf::Text buttonText;
};
