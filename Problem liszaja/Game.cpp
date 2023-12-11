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
                
            if (currentround != 1 && currentround <= duration->maxround && !menuOpen) {
                if (board->countCells(Health, board->size) == board->size * board->size) {
                    cout << "Koniec Gry: Wszystkie komorki zdrowe" << endl;
                    duration->delay(5, window);
                    window.close();
                    break;
                }

                if (board->countCells(Infected, board->size) == board->size * board->size) {
                    cout << "Koniec Gry: Wszystkie komorki chore" << endl;
                    duration->delay(5, window);
                    window.close();
                    break;
                }

                deltaTime = clock.restart().asSeconds();
                allTime += deltaTime;

                duration->delay(duration->holdprocess, window);
                board->update(board->size, currentround, deltaTime, allTime, window, duration->infectionPercent, duration->infectedToImmune, duration->immuneCooldown);
                
                window.clear();
                board->drawBoard(window);
                window.display();
                
                currentround++;
            }    
        }
    }

    return 0;
}
