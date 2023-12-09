#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu{
public:
	void drawMenu(sf::RenderWindow& window);
private:
	sf::Font font;
	sf::Text title;
};

