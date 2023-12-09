#include "Game.h"
using namespace std;
using namespace sf;

int Game::run(){

    board.consoleStart();
    duration.consoleStart();

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Problem liszaja", sf::Style::Titlebar | sf::Style::Close);

    bool gameStarted = false;
    int currentround = 1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            /*
            if (!gameStarted) {

            }
            */
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (!gameStarted) {
                    gameStarted = true;
                }
                if (currentround == 1) {
                    window.clear();
                    board.calculateboardSize(window);
                    board.handleClick(currentround, window);
                    board.drawBoard(window);
                    menu.drawMenu(window);
                    window.display();
                    currentround = 2;
                }
            }
            if (currentround != 1 && currentround <= duration.maxround) {
                for (currentround = 2; currentround <= duration.maxround; currentround++) {
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
                }
            }
        }
        window.clear();
        board.drawBoard(window);
        window.display();
    }
    
    return 0;
}
