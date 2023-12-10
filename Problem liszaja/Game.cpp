#include "Game.h"
using namespace std;
using namespace sf;

int Game::run() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Problem liszaja", sf::Style::Titlebar | sf::Style::Close);

    bool gameStarted = false;
    bool gamePause = true;
    bool menuOpen = true;
    int currentround = 1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) {
                if (menuOpen && gamePause) {
                    menuOpen = false;
                    gamePause = false;
                }
                else if (!menuOpen && !gamePause) {
                    menuOpen = true;
                    gamePause = true;
                }
            }

            if (menuOpen) {
                window.clear();
                menu.drawMenu(window);
                window.display();
            }
            else {
                if (!gameStarted) {
                    gameStarted = true;
                }
                
                if (currentround == 1) {
                    window.clear();
                    board.calculateboardSize(window);
                    board.handleClick(currentround, window);
                    board.drawBoard(window);
                    window.display();
                    currentround = 2;
                }

                if (currentround != 1 && currentround <= duration.maxround) {
                    if (board.countCells(Health, board.size) == board.size * board.size) {
                        cout << "Koniec Gry: Wszystkie komorki zdrowe" << endl;
                        duration.delay(5, window);
                        window.close();
                        break;
                    }

                    if (board.countCells(Infected, board.size) == board.size * board.size) {
                        cout << "Koniec Gry: Wszystkie komorki chore" << endl;
                        duration.delay(5, window);
                        window.close();
                        break;
                    }

                    deltaTime = clock.restart().asSeconds();
                    allTime += deltaTime;

                    duration.delay(duration.holdprocess, window);
                    board.update(board.size, currentround, deltaTime, allTime, window, duration.infectionPercent, duration.infectedToImmune, duration.immuneCooldown);
                    window.clear();
                    board.drawBoard(window);
                    window.display();
                    currentround++;
                }
                
            }
        }

        window.clear();
        if (menuOpen) {
            menu.drawMenu(window);
        }
        else {
            board.drawBoard(window);
        }
        window.display();
    }

    return 0;
}
