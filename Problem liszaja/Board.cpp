#include "Board.h"

Board::Board(unsigned int size) : size(size), timer(0.0f) {
    // Initialize the vector of health statuses for each cell
    healthStatuses.resize(size, std::vector<HealthStatus>(size, Health));

    // Inicjalizacja wektora kolorów dla ka¿dego pola
    colors.resize(size, std::vector<sf::Color>(size, sf::Color::Green));
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
            switch (healthStatuses[i][j]) {
            case Health:
                cell.setFillColor(sf::Color::Green);
                break;
            case Immune:
                cell.setFillColor(sf::Color::Yellow);
                break;
            case Infected:
                cell.setFillColor(sf::Color::Red);
                break;
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

    sf::Text Title("Problem liszaja", font, 30);
    sf::FloatRect TitleRect = Title.getLocalBounds();
    Title.setOrigin(TitleRect.left + TitleRect.width / 2.0f, TitleRect.top + TitleRect.height / 2.0f);
    Title.setPosition(sf::Vector2f(offsetX + boardSize / 2.0f, offsetY - 50.0f));
    window.draw(Title);

    float textOffsetX = offsetX + boardSize + 20.0f;
    sf::Text text("Chuj", font, 20);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(textOffsetX + textRect.width, offsetY + 30.0f));
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
        cout << "Status" << healthStatuses[row][col] << "   ";
        cout << "Clicked on cell: (" << row << ", " << col << ")" << endl;

        // Zaznaczanie wybranego pola na czerwono
        highlightCell(row, col, window, Infected);

        // Spread infection for the initially infected cell
        spreadInfection(row, col);
    }
}

// Zaktualizowana funkcja highlightCell
void Board::highlightCell(unsigned int row, unsigned int col, sf::RenderWindow& window, HealthStatus newStatus) {
    healthStatuses[row][col] = newStatus;
    colors[row][col] = sf::Color::Red;  // Zaznaczanie wybranego pola na czerwono (zmiana koloru)

    // Odœwie¿ widok
    window.display();
}

void Board::update(float deltaTime, sf::RenderWindow& window) {
    // Update the timer
    timer += deltaTime;
    
    // Check for infection spread every infectionInterval seconds
    if (timer >= infectionInterval) {
        // Iterate through the cells and spread infection
        for (unsigned int i = 0; i < size; ++i) {
            for (unsigned int j = 0; j < size; ++j) {
                if (healthStatuses[i][j] == Infected) {
                    spreadInfection(i, j);
                }
            }
        }
        cout << "timer " << timer << endl;
        // Reset the timer
        timer = 0.0f;
    }

    // Check for transitioning Infected cells to Immune
    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = 0; j < size; ++j) {
            if (healthStatuses[i][j] == Infected && timer >= immuneDuration) {
                highlightCell(i, j, window, Immune);
            }
        }
    }

    draw(window);
}

#include <random>

void Board::spreadInfection(unsigned int row, unsigned int col) {
    // Define a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Check adjacent cells and infect them with a 50% chance
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            // Skip the current cell
            if (i == 0 && j == 0) {
                continue;
            }

            // Calculate the adjacent cell indices
            int newRow = static_cast<int>(row) + i;
            int newCol = static_cast<int>(col) + j;

            // Check if the adjacent cell is within the board boundaries
            if (newRow >= 0 && newRow < static_cast<int>(size) &&
                newCol >= 0 && newCol < static_cast<int>(size)) {

                // Check if the adjacent cell is healthy and infect it with a 50% chance
                if (healthStatuses[newRow][newCol] == Health && dis(gen) < 0.5) {
                    // Change status to Infected
                    healthStatuses[newRow][newCol] = Infected;

                    // Change color to indicate infection
                    colors[newRow][newCol] = sf::Color::Red;
                }
            }
        }
    }
}
