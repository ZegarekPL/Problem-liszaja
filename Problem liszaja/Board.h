#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

// Avoid using "using namespace" in header files
enum HealthStatus {
    Health,
    Immune,
    Infected
};

class Board {
public:
    Board(unsigned int size);
    void draw(sf::RenderWindow& window);
    void handleClick(sf::RenderWindow& window);
    void redCell(unsigned int row, unsigned int col, sf::RenderWindow& window, HealthStatus newStatus);
    void update(int currentRound, float deltaTime, sf::RenderWindow& window);

private:
    float cellSize = 50.0f;
    float boardSize;
    float offsetX;
    float offsetY;
    sf::Font font;
    unsigned int size;
    std::vector<std::vector<HealthStatus>> healthStatuses;
    std::vector<std::vector<sf::Color>> colors;

    const float infectionInterval = 1.0f;
    const float immuneDuration = 3.0f;
    float timer = 0.0f;

    void spreadInfection(unsigned int row, unsigned int col);
};
