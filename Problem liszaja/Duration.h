#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Duration {
public:
    Duration(int maxround, unsigned int holdprocess, int infectionPercent, unsigned int infectedToImmune, unsigned int immuneCooldown);
	void delay(int time, sf::RenderWindow& window);
	void consoleStart();
    int maxround;
    unsigned int holdprocess;
    int infectionPercent;
    unsigned int infectedToImmune;
    unsigned int immuneCooldown;
};
