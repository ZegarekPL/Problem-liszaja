#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Duration {
public:
	void delay(int time, sf::RenderWindow& window);
	void consoleStart();
    float maxround;
    unsigned int holdprocess;
    float infectionPercent;
    unsigned int infectedToImmune;
    unsigned int immuneCooldown;
};
