#include "Board.h"

Board::Board(unsigned int size) : size(size) {
    // Konstruktor, mo¿esz dodaæ kod inicjalizuj¹cy, jeœli to konieczne
}

void Board::draw(sf::RenderWindow& window) {
    // Rysowanie planszy "x na x"
    for (unsigned int i = 0; i < size; ++i) {
        sf::Vertex line1[] = {
            sf::Vertex(sf::Vector2f(i * 50, 0)),
            sf::Vertex(sf::Vector2f(i * 50, size * 50))
        };

        sf::Vertex line2[] = {
            sf::Vertex(sf::Vector2f(0, i * 50)),
            sf::Vertex(sf::Vector2f(size * 50, i * 50))
        };

        window.draw(line1, 2, sf::Lines);
        window.draw(line2, 2, sf::Lines);
    }
}
