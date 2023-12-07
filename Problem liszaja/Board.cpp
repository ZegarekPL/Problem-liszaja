#include "Board.h"

Board::Board() {

}

void Board::consoleStart() {

    do {
        std::cout << "Wpisz liczbe pol x: ";
        std::cin >> size;

        if (size <= 0 || size > 11) {
            std::cout << "Error: Too large area!!! Try again." << std::endl;
        }
    } while (size <= 0 || size > 11);

    healthStatuses.resize(size, std::vector<HealthStatus>(size, Health));
    colors.resize(size, std::vector<sf::Color>(size, sf::Color::Green));
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
    }
}

void Board::update(int boardSize,int currentround, float deltaTime, sf::RenderWindow& window, float infectionPercent, int infectedToImmune, int immuneCooldown) {
    // Iterate through the cells and spread infection
    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = 0; j < size; ++j) {
            if (healthStatuses[i][j] == Infected) {
                findRowAndCol(i, j, currentround, infectionPercent);
            }
        }
    }
    
    spreadInfection(data, currentround, infectedToImmune, immuneCooldown); 
    drawData(data);

    std::cout << "currentround " << currentround << std::endl;
    std::cout << "deltaTime " << deltaTime << std::endl;
    std::cout << "timer " << timer << std::endl;

    cout << "Health: " << countCells(Health, boardSize) << endl;
    cout << "Infected: " << countCells(Infected, boardSize) << endl;
    cout << "Immune: " << countCells(Immune, boardSize) << endl;
    cout << "Infected+Immune: " << countCells(Infected, boardSize) + countCells(Immune, boardSize) << endl;
    cout << "Health+Infected+Immune: " << countCells(Health, boardSize) + countCells(Infected, boardSize) + countCells(Immune, boardSize) << endl;
    cout << "Data: " << data.size() << endl << endl << endl;

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

void Board::findRowAndCol(unsigned int row, unsigned int col, int currentround, float infectionPercent) {

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

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
                    newCol >= 0 && newCol < static_cast<int>(size) &&
                    dis(gen) < infectionPercent &&
                    healthStatuses[newRow][newCol] == Health) {

                    addToData(currentround, newRow, newCol);
                }
            }
        }
    }
}

void Board::addToData(int currentroun, int newRow, int newCol) {
    data.push_back({ make_tuple(currentroun, newRow, newCol) });
}

void Board::drawData(vector<vector<tuple<int, int, int>>>& data) {
    for (const auto& roundData : data) {
        for (const auto& cell : roundData) {
            int round = get<0>(cell);
            int row = get<1>(cell);
            int col = get<2>(cell);

            cout << "( " << round << " " << row << " " << col << " " << healthStatuses[row][col] << ")" << endl;
        }
    }
    cout << "Data: " << data.size() << endl;
}

void Board::spreadInfection(vector<vector<tuple<int, int, int>>>& data, int currentround, int infectedToImmune, int immuneCooldown) {

    for (const auto& roundData : data) {
        for (const auto& cell : roundData) {
            int round = get<0>(cell);
            int row = get<1>(cell);
            int col = get<2>(cell);

            if (currentround == 5) {
                cout << "DUPAspreadInfection " << endl;
            }

            if (healthStatuses[row][col] == Health) {
                // Je¿eli tak, to zmieñ status na "Infected"
                healthStatuses[row][col] = Infected;
                continue;
            }
            if (healthStatuses[row][col] == Infected && currentround - round >= infectedToImmune) {
                // Je¿eli tak, to zmieñ status na "Immune"
                healthStatuses[row][col] = Immune;
                continue;
            }
            if (healthStatuses[row][col] == Immune && currentround - round >= infectedToImmune + immuneCooldown) {
                // Je¿eli tak, to zmieñ status na "Health"
                healthStatuses[row][col] = Health;
                continue;
            }
            else continue;
        }
    }
    removeHealthCells(data, currentround, infectedToImmune, immuneCooldown);
}

void Board::removeHealthCells(vector<vector<tuple<int, int, int>>>& data, int currentround, int infectedToImmune, int immuneCooldown) {

    if (currentround == 5) {
        cout << "DUPA " << endl;
    }
    vector<int> toErase;
    for (int i = 0; i < data.size(); i++) {
        for (const auto& cell : data[i]) {
            int round = get<0>(cell);
            int row = get<1>(cell);
            int col = get<2>(cell);

            if (healthStatuses[row][col] == Health) {
                toErase.push_back(i);
                cout << "( TO ERASE " << round << " " << row << " " << col << " " << healthStatuses[row][col] << ")" << endl;
            }

        }
    }
    int licznik = 0;

    for (auto index : toErase) {
        data.erase(data.begin() + index-licznik);
        licznik++;
    }
}

int Board::countCells(HealthStatus status, int boardSize) {
    int count = 0;

    for (unsigned int i = 0; i < boardSize; ++i) {
        for (unsigned int j = 0; j < boardSize; ++j) {
            if (healthStatuses[i][j] == status) {
                count++;
            }
        }
    }
    return count;
}