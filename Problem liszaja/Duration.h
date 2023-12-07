#pragma once
#include "Board.h"
#include <SFML/Window.hpp>

class Duration {
public:
	void delay(int time, Board* board, sf::RenderWindow& window);

};
