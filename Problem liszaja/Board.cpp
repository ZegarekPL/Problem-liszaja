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


void Board::calculateboardSize(sf::RenderWindow& window) {
    boardSize = size * cellSize;
    offsetX = (window.getSize().x - boardSize) / 2.0f;
    offsetY = (window.getSize().y - boardSize) / 2.0f;
}


void Board::drawBoard(sf::RenderWindow& window) {

    calculateboardSize(window);

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
    title = sf::Text("Problem liszaja", font, 30);
    sf::FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
    title.setPosition(sf::Vector2f(offsetX + boardSize / 2.0f, offsetY - 50.0f));
    window.draw(title);

    window.draw(deltaText);
    window.draw(text);
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
        addTotoStore(currentround, row, col);
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
    
    spreadInfection(toStore, currentround, infectedToImmune, immuneCooldown); 
    //drawtoStore(toStore);

    std::cout << "currentround " << currentround << std::endl;
    std::cout << "deltaTime " << deltaTime << std::endl;
    std::cout << "timer " << timer << std::endl;

    cout << "Health: " << countCells(Health, boardSize) << endl;
    cout << "Infected: " << countCells(Infected, boardSize) << endl;
    cout << "Immune: " << countCells(Immune, boardSize) << endl;
    cout << "Infected+Immune: " << countCells(Infected, boardSize) + countCells(Immune, boardSize) << endl;
    cout << "Health+Infected+Immune: " << countCells(Health, boardSize) + countCells(Infected, boardSize) + countCells(Immune, boardSize) << endl;


    // Dodawanie czcionki
    if (!font.loadFromFile("Inter-Medium.ttf")) {
        std::cout << "Error: B³¹d ³adowania czcionki" << std::endl;
        return;
    }

    float deltaTimeOffsetX = offsetX + boardSize + 20.0f;
    deltaText = sf::Text("Delta Czasu: " + std::to_string(deltaTime), font, 20);
    sf::FloatRect deltaTextRect = deltaText.getLocalBounds();
    deltaText.setOrigin(deltaTextRect.left + deltaTextRect.width / 2.0f, deltaTextRect.top + deltaTextRect.height / 2.0f);
    deltaText.setPosition(sf::Vector2f(deltaTimeOffsetX + deltaTextRect.width, offsetY + 30.0f));
    
    float textOffsetX = offsetX + boardSize + 100.0f;
    text = sf::Text("Delta Czasu: " + std::to_string(deltaTime), font, 20);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(textOffsetX + textRect.width, offsetY + 50.0f));
   
    drawBoard(window);
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
                if ((i == 0 && j == 0) ||
                    (i == -1 && j == -1) ||
                    (i == -1 && j == 1) ||
                    (i == 1 && j == -1) ||
                    (i == 1 && j == 1)) {
                    continue;
                }

                // Calculate the adjacent cell indices
                int newRow = static_cast<int>(row) + i;
                int newCol = static_cast<int>(col) + j;

                //Chech if cell is in board  
                if (newRow >= 0 && newRow < static_cast<int>(size) &&
                    newCol >= 0 && newCol < static_cast<int>(size) &&
                    dis(gen) < infectionPercent &&
                    healthStatuses[newRow][newCol] == Health &&
                    !isInToStore(currentround, newRow, newCol)) {

                    addTotoStore(currentround, newRow, newCol);
                }
            }
        }
    }
}

void Board::addTotoStore(int currentroun, int newRow, int newCol) {
    toStore.push_back({ make_tuple(currentroun, newRow, newCol) });
}

bool Board::isInToStore(int currentround, int newRow, int newCol) {
    // Przeszukaj wektor toStore w poszukiwaniu elementu
    auto it = find_if(toStore.begin(), toStore.end(), [currentround, newRow, newCol](const tuple<int, int, int>& element) {
        return get<0>(element) == currentround && get<1>(element) == newRow && get<2>(element) == newCol;
        });
    return it != toStore.end();
}

void Board::drawtoStore(vector<tuple<int, int, int>>& toStore) {
    for (const auto& roundtoStore : toStore) {
        int round = get<0>(roundtoStore);
        int row = get<1>(roundtoStore);
        int col = get<2>(roundtoStore);

        cout << "( " << round << " " << row << " " << col << " " << healthStatuses[row][col] << ")" << endl;
    }
    cout << "toStore: " << toStore.size() << endl;
}

void Board::spreadInfection(vector<tuple<int, int, int>>& toStore, int currentround, int infectedToImmune, int immuneCooldown) {

    

    for (int i = 0; i < toStore.size(); i++) {
        int round = get<0>(toStore[i]);
        int row = get<1>(toStore[i]);
        int col = get<2>(toStore[i]);

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
    removeHealthCells(toStore, currentround, infectedToImmune, immuneCooldown);
}

void Board::removeHealthCells(vector<tuple<int, int, int>>& toStore, int currentround, int infectedToImmune, int immuneCooldown) {

    vector<int> toErase;

    int i;
    for (i = 0; i < toStore.size(); i++) {
        int round = get<0>(toStore[i]);
        int row = get<1>(toStore[i]);
        int col = get<2>(toStore[i]);

        if (healthStatuses[row][col] == Health) {
            toErase.push_back(i);
        }
    }

    int licznik = 0;

    int j;
    for (int j = 0; j < toErase.size(); ++j) {
        int index = toErase[j] - licznik;
        if (index >= 0 && index < toStore.size()) {
            toStore.erase(toStore.begin() + index);
            licznik++;
        }
    }
}

int Board::countCells(HealthStatus status, int boardSize) {

    int count = 0;
    unsigned int i;
    unsigned int j;

    for (i = 0; i < boardSize; ++i) {
        for (j = 0; j < boardSize; ++j) {
            if (healthStatuses[i][j] == status) {
                count++;
            }
        }
    }
    return count;
}
