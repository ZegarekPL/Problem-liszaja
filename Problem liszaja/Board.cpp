#include "Board.h"

Board::Board(unsigned int size) : size(size) {
    // Inicjalizacja wektora kolorów dla ka¿dego pola
    colors.resize(size, std::vector<sf::Color>(size, sf::Color::White));
}

void Board::draw(sf::RenderWindow& window) {
    float cellSize = 50.0f;
    float boardSize = size * cellSize;
    float offsetX = (window.getSize().x - boardSize) / 2.0f;
    float offsetY = (window.getSize().y - boardSize) / 2.0f;

    // Rysowanie siatki i kolorowanie pó
    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = 0; j < size; ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(offsetX + j * cellSize, offsetY + i * cellSize);

            // Zmiana koloru pola na czarny, jeœli jest bia³e
            if (colors[i][j] == sf::Color::White) {
                cell.setFillColor(sf::Color::Black);
            }
            else {
                cell.setFillColor(colors[i][j]);
            }

            window.draw(cell);
        }
    }

    for (unsigned int i = 0; i < size + 1; ++i) {
        for (unsigned int j = 0; j < size + 1; ++j) {
            // Rysowanie poprzerywanych bia³ych linii poziomych
            sf::RectangleShape horizontalLine(sf::Vector2f(boardSize, 1.0f));
            horizontalLine.setPosition(offsetX, offsetY + i * cellSize);
            horizontalLine.setFillColor(sf::Color::White);
            window.draw(horizontalLine);

            // Rysowanie poprzerywanych bia³ych linii pionowych
            sf::RectangleShape verticalLine(sf::Vector2f(1.0f, boardSize));
            verticalLine.setPosition(offsetX + j * cellSize, offsetY);
            verticalLine.setFillColor(sf::Color::White);
            window.draw(verticalLine);
        }
    }

    // Dodanie napisu
    sf::Font font;
    if (!font.loadFromFile("Inter-Medium.ttf")) {
        cout << "Error: Blad ladowania czcionki" << endl;
        return;
    }

    sf::Text text("Problem liszaja", font, 30);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(offsetX + boardSize / 2.0f, offsetY - 50.0f));

    window.draw(text);
}

void Board::handleClick(sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    float cellSize = 50.0f;
    float offsetX = (window.getSize().x - size * cellSize) / 2.0f;
    float offsetY = (window.getSize().y - size * cellSize) / 2.0f;

    // Sprawdzanie, czy mysz znajduje siê nad plansz¹
    if (mousePosition.x >= offsetX && mousePosition.x <= offsetX + size * cellSize &&
        mousePosition.y >= offsetY && mousePosition.y <= offsetY + size * cellSize) {

        // Znajdowanie indeksu kolumny i wiersza, na który klikniêto
        unsigned int col = static_cast<unsigned int>((mousePosition.x - offsetX) / cellSize);
        unsigned int row = static_cast<unsigned int>((mousePosition.y - offsetY) / cellSize);

        // Wypisanie indeksów klikniêtego pola
        cout << "Clicked on cell: (" << row << ", " << col << ")" << endl;

        // Zaznaczanie wybranego pola na czerwono
        highlightCell(row, col, window);
    }
}

// Zaktualizowana funkcja highlightCell
void Board::highlightCell(unsigned int row, unsigned int col, sf::RenderWindow& window) {


    colors[row][col] = sf::Color::Red;

    // Odœwie¿ widok
    window.display();
}
