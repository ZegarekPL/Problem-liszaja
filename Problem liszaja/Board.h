#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Duration.h"
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
    void drawBoard(sf::RenderWindow& window);
    void calculateboardSize(sf::RenderWindow& window);
    void handleClick(int currentround, sf::RenderWindow& window);
    void update(int boardSize, int currentRound, float deltaTime, float allTime, sf::RenderWindow& window, int infectionPercent, int infectedToImmune, int immuneCooldown);
    unsigned int size;
    int countCells(HealthStatus status, int boardSize);
private:
    float cellSize;
    float boardSize = 550.0f;
    float offsetX;
    float offsetY;
    sf::Font font;
    Duration duration;

    vector<vector<HealthStatus>> healthStatuses;
    vector<vector<sf::Color>> colors;

    sf::Text title;
    sf::Text roundText;
    sf::Text deltaTimeText;
    sf::Text allTimeText;
    sf::Text allCellText;
    sf::Text infectedCellText;
    sf::Text immuneCellText;
    sf::Text healthCellText;

    vector<tuple<int, int, int>> toStore;
    void findRowAndCol(unsigned int row, unsigned int col, int currentround, float infectionPercent);
    void addTotoStore(int newRow, int newCol, int currentround);
    bool isInToStore(int currentround, int newRow, int newCol);
    void drawtoStore(vector<tuple<int, int, int>>& toStore);
    void spreadInfection(vector<tuple<int, int, int>>& toStore, int currentround, int infectedToImmune, int immuneCooldown);
    void removeHealthCells(vector<tuple<int, int, int>>& toStore, int currentround, int infectedToImmune, int immuneCooldown);
};
