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
    void handleClick(int currentround, sf::RenderWindow& window);
    void update(int currentRound, float deltaTime, sf::RenderWindow& window);
private:
    float cellSize = 50.0f;
    float boardSize;
    float offsetX;
    float offsetY;
    sf::Font font;
    unsigned int size;
    vector<vector<HealthStatus>> healthStatuses;
    vector<vector<sf::Color>> colors;

    const float infectionInterval = 1.0f;
    const float immuneDuration = 3.0f;
    float timer = 0.0f;

    vector<vector<tuple<int, int, int>>> data;
    void findRowAndCol(unsigned int row, unsigned int col, int currentround);
    void addToData(int newRow, int newCol, int currentround);
    void drawData(const vector<vector<tuple<int, int, int>>>& data);
    void spreadInfection(const vector<vector<tuple<int, int, int>>>& data);
};
