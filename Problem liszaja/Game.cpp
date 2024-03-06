#include "Game.h"
using namespace std;
using namespace sf;

int Game::run() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Problem liszaja", sf::Style::Titlebar | sf::Style::Close);
    this->menu = new Menu();
    bool gameStarted = false;
    bool menuOpen = true;
    int currentround = 1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }  

            if (menuOpen) {
                window.clear();
                menu->drawMenu(window);
                window.display();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) {
                if (menuOpen) {
                    menuOpen = false;
                    if (this->isFirst) {
                        delete this->board;
                        this->board = new Board(menu->menuSize);
                        this->board->updateSize(menu->menuSize);
                        this->isFirst = false;
                    }
                    delete this->duration;
                    this->duration = new Duration(menu->menuMaxround, menu->menuHoldprocess, menu->menuInfectionPercent, menu->menuInfectedToImmune, menu->menuImmuneCooldown);
                    board->calculateboardSize(window);
                }
                else if (!menuOpen) {
                    menuOpen = true;
                }
            }

            if (currentround == 1 && !gameStarted && !menuOpen) {

                window.clear();
                board->drawBoard(window);
                window.display();
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    board->handleClick(currentround, window);
                    gameStarted = true;
                    currentround = 2;
                }     
            }
                
            if (currentround != 1) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    board->handleClick(currentround, window);
                }

                if (board->countCells(Health, board->size) == board->size * board->size) {
                    cout << "Koniec Gry: Wszystkie komorki zdrowe" << endl;
                    
                    window.clear();
                    drawEndAllHealth(window);
                    window.display();
                    delay(5, window, menuOpen);
                    window.close();
                    break;
                }

                if (board->countCells(Infected, board->size) == board->size * board->size) {
                    cout << "Koniec Gry: Wszystkie komorki chore" << endl;                  
                    window.clear();
                    drawEndAllInfected(window);
                    window.display();
                    delay(5, window, menuOpen);
                    window.close();
                    break;
                }

                if (!menuOpen) {
                    deltaTime = clock.restart().asSeconds();
                    if (deltaTime >= 1) {
                        cout << "deltaTime" << deltaTime << endl;
                    }
                    allTime += deltaTime;

                    delay(duration->holdprocess, window, menuOpen);
                    board->update(board->size, currentround, deltaTime, allTime, window, duration->infectionPercent, duration->infectedToImmune, duration->immuneCooldown);

                    window.clear();
                    board->drawBoard(window);
                    window.display();

                    currentround++;
                } 
            }    
        }
    }

    return 0;
}
void Game::delay(int time, sf::RenderWindow& window, bool& menuOpen) {
    sf::Clock delayClock;
    delayClock.restart();
    time *= 1000;
    while (delayClock.getElapsedTime().asMilliseconds() < time) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) {
                if (menuOpen) {
                    menuOpen = false;
                    this->board = new Board(menu->menuSize);
                    this->duration = new Duration(menu->menuMaxround, menu->menuHoldprocess, menu->menuInfectionPercent, menu->menuInfectedToImmune, menu->menuImmuneCooldown);
                    board->calculateboardSize(window);
                    break;
                }
                else if (!menuOpen) {
                    menuOpen = true;
                    break;
                }
            }
        }
    }
}

void Game::drawEndAllHealth(sf::RenderWindow& window) {
    // Dodawanie czcionki
    if (!font.loadFromFile("Inter-Medium.ttf")) {
        std::cout << "Error: B³¹d ³adowania czcionki" << std::endl;
        return;
    }

    // Pomarañczowe t³o
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(0, 0, 0, 128));
    window.draw(background);

    // Dodanie napisu
    exitHealth = sf::Text("Koniec Gry: Wszystkie komorki zdrowe", font, 25);
    sf::FloatRect exitRect = exitHealth.getLocalBounds();
    exitHealth.setOrigin(exitRect.left + exitRect.width / 2.0f, exitRect.top + exitRect.height / 2.0f);
    exitHealth.setPosition(sf::Vector2f(640.0f, 300.0f));
    window.draw(exitHealth);
}

void Game::drawEndAllInfected(sf::RenderWindow& window) {
    // Dodawanie czcionki
    if (!font.loadFromFile("Inter-Medium.ttf")) {
        std::cout << "Error: B³¹d ³adowania czcionki" << std::endl;
        return;
    }

    // Pomarañczowe t³o
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(0, 0, 0, 128));
    window.draw(background);

    // Dodanie napisu
    exitInfected = sf::Text("Koniec Gry: Wszystkie komorki chore", font, 25);
    sf::FloatRect exitRect = exitInfected.getLocalBounds();
    exitInfected.setOrigin(exitRect.left + exitRect.width / 2.0f, exitRect.top + exitRect.height / 2.0f);
    exitInfected.setPosition(sf::Vector2f(640.0f, 300.0f));
    window.draw(exitInfected);
}