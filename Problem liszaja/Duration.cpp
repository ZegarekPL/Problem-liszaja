#include "Duration.h"

void Duration::delay(int time, Board* board, sf::RenderWindow& window) {
    sf::Clock delayClock;
    delayClock.restart();
    time *= 1000;
    while (delayClock.getElapsedTime().asMilliseconds() < time) {
        board->draw(window);
    }
}