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
                
            if (currentround != 1 && currentround <= duration->maxround) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    board->handleClick(currentround, window);
                }

                if (board->countCells(Health, board->size) == board->size * board->size) {
                    cout << "Koniec Gry: Wszystkie komorki zdrowe" << endl;
                    delay(5, window, menuOpen);
                    window.close();
                    break;
                }

                if (board->countCells(Infected, board->size) == board->size * board->size) {
                    cout << "Koniec Gry: Wszystkie komorki chore" << endl;
                    delay(5, window, menuOpen);
                    window.close();
                    break;
                }

                if (!menuOpen) {
                    deltaTime = clock.restart().asSeconds();
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