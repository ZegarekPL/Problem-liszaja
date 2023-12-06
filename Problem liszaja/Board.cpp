#include "Board.h"

Board::Board(unsigned int size) : size(size), timer(0.0f) {
    healthStatuses.resize(size, std::vector<HealthStatus>(size, Health));   // Initialize the vector of health statuses for each cell
    colors.resize(size, std::vector<sf::Color>(size, sf::Color::Green));    // Initialize the vector of colors for each cell
}

void Board::draw(sf::RenderWindow& window) {
    boardSize = size * cellSize;
    offsetX = (window.getSize().x - boardSize) / 2.0f;
    offsetY = (window.getSize().y - boardSize) / 2.0f;

    // Rysowanie siatki i kolorowanie komórek
    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = 0; j < size; ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(offsetX + j * cellSize, offsetY + i * cellSize);

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

    // Rysowanie siatki
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

    // Dodawanie czcionki
    if (!font.loadFromFile("Inter-Medium.ttf")) {
        std::cout << "Error: B³¹d ³adowania czcionki" << std::endl;
        return;
    }

    // Dodanie napisu
    sf::Text title("Problem liszaja", font, 30);
    sf::FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
    title.setPosition(sf::Vector2f(offsetX + boardSize / 2.0f, offsetY - 50.0f));
    window.draw(title);
}

void Board::handleClick(int currentround, sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    // Sprawdzanie, czy mysz znajduje siê nad plansz¹
    if (mousePosition.x >= offsetX && mousePosition.x <= offsetX + boardSize &&
        mousePosition.y >= offsetY && mousePosition.y <= offsetY + boardSize) {

        // Znajdowanie indeksu kolumny i wiersza, na który klikniêto
        unsigned int col = static_cast<unsigned int>((mousePosition.x - offsetX) / cellSize);
        unsigned int row = static_cast<unsigned int>((mousePosition.y - offsetY) / cellSize);

        // Wypisanie indeksów klikniêtego pola
        cout << "Clicked on cell: (" << row << ", " << col << ")" << std::endl;

        // Zaznaczanie wybranego pola na czerwono
        healthStatuses[row][col] = Infected;
        addToData(currentround, row, col);
        drawData(data);
    }
}

void Board::update(int currentround, float deltaTime, sf::RenderWindow& window) {
    // Iterate through the cells and spread infection
    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = 0; j < size; ++j) {
            if (healthStatuses[i][j] == Infected) {
                findRowAndCol(i, j, currentround);
                drawData(data);
            }
        }
    }

    std::cout << "currentround " << currentround << std::endl;
    std::cout << "deltaTime " << deltaTime << std::endl;
    std::cout << "timer " << timer << std::endl;

    float deltaTimeOffsetX = offsetX + boardSize + 20.0f;
    sf::Text deltaText("Delta Czasu: " + std::to_string(deltaTime), font, 20);
    sf::FloatRect deltaTextRect = deltaText.getLocalBounds();
    deltaText.setOrigin(deltaTextRect.left + deltaTextRect.width / 2.0f, deltaTextRect.top + deltaTextRect.height / 2.0f);
    deltaText.setPosition(sf::Vector2f(deltaTimeOffsetX + deltaTextRect.width, offsetY + 30.0f));
    window.draw(deltaText);

    float textOffsetX = offsetX + boardSize + 20.0f;
    sf::Text text("Delta Czasu: " + std::to_string(deltaTime), font, 20);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(textOffsetX + textRect.width, offsetY + 50.0f));
    window.draw(text);

    draw(window);
}

#include <random>
#include <set>

void Board::findRowAndCol(unsigned int row, unsigned int col, int currentround) {

    if (healthStatuses[row][col] == Infected) {     // Check if the current cell is infected
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                // Skip the current cell
                if (i == 0 && j == 0) {
                    continue;
                }

                // Calculate the adjacent cell indices
                int newRow = static_cast<int>(row) + i;
                int newCol = static_cast<int>(col) + j;

                //Chech if cell is in board  
                if (newRow >= 0 && newRow < static_cast<int>(size) &&
                    newCol >= 0 && newCol < static_cast<int>(size)) {

                    addToData(currentround, newRow, newCol);
                }
            }
        }
    }
}

void Board::addToData(int currentroun, int newRow, int newCol) {
    data.push_back({ make_tuple( newRow, newCol) });
}

void Board::drawData(const vector<vector<tuple<int, int>>>& data) {
    cout << "Contents of the 2D vector:" << endl;
    for (const auto& roundData : data) {
        for (const auto& cell : roundData) {
            int row = get<0>(cell);
            int col = get<1>(cell);

            cout << "( " << row << ", " << col << ") ";
        }
        cout << endl;
    }
}

/*
            // SprawdŸ, czy komórka ma status "Health"
            if (healthStatuses[row][col] == Health && healthStatuses[row][col]) {
                // Je¿eli tak, to zmieñ status na "Infected"
                healthStatuses[row][col] = Infected;
                cout << "chuj ";
            }
            else continue;
            */