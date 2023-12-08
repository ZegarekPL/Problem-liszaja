#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;


enum HealthStatus {
    Health,
    Immune,
    Infected
};

class Board {
public:
    Board();
    void consoleStart();
    void draw(sf::RenderWindow& window);
    void handleClick(int currentround, sf::RenderWindow& window);
    void update(int boardSize, int currentRound, float deltaTime, sf::RenderWindow& window, float infectionPercent, int infectedToImmune, int immuneCooldown);
    unsigned int size;
private:
    float cellSize = 50.0f;
    float boardSize;
    float offsetX;
    float offsetY;
    sf::Font font;
    
    vector<vector<HealthStatus>> healthStatuses;
    vector<vector<sf::Color>> colors;

    const float infectionInterval = 1.0f;
    const float immuneDuration = 3.0f;
    float timer = 0.0f;

    vector<tuple<int, int, int>> toStore;
    void findRowAndCol(unsigned int row, unsigned int col, int currentround, float infectionPercent);
    void addTotoStore(int newRow, int newCol, int currentround);
    bool isInToStore(int currentround, int newRow, int newCol);
    void drawtoStore(vector<tuple<int, int, int>>& toStore);
    void spreadInfection(vector<tuple<int, int, int>>& toStore, int currentround, int infectedToImmune, int immuneCooldown);
    void removeHealthCells(vector<tuple<int, int, int>>& toStore, int currentround, int infectedToImmune, int immuneCooldown);
    int countCells(HealthStatus status, int boardSize);
};
