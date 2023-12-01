#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

// Add health statuses enumeration
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
    void highlightCell(unsigned int row, unsigned int col, sf::RenderWindow& window, HealthStatus newStatus);
    void update(float deltaTime, sf::RenderWindow& window);
    float timer=0;

private:
    float cellSize = 50.0f;
    float boardSize;
    float offsetX;
    float offsetY;
    sf::Font font;
    unsigned int size;
    std::vector<std::vector<HealthStatus>> healthStatuses;
    std::vector<std::vector<sf::Color>> colors;

    // Add a timer for tracking time-based events
    const float infectionInterval = 1.0f; // Adjust this value as needed
    const float immuneDuration = 3.0f;     // Adjust this value as needed

    // Function to handle infection spread
    void spreadInfection(unsigned int row, unsigned int col);

};
