#include "Game.h"
using namespace std;
using namespace sf;

int Game::run(){

    Board board;

    board.consoleStart();
    duration.consoleStart();

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Problem liszaja", sf::Style::Titlebar | sf::Style::Close);

    bool gameStarted = false;
    int currentround = 1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (!gameStarted) {
                    gameStarted = true;
                }
                if (currentround == 1) {
                    window.clear();
                    board.handleClick(currentround, window);
                    board.draw(window);
                    window.display();
                    cout << "All: " << board.size * board.size << endl;
                    currentround = 2;
                }
            }
            if (currentround != 1 && currentround <= duration.maxround) {
                for (currentround = 2; currentround <= duration.maxround; currentround++) {
                    float deltaTime = clock.restart().asSeconds();
                    
                    duration.delay(duration.holdprocess, &board, window);
                    board.update(board.size, currentround, deltaTime, window, duration.infectionPercent, duration.infectedToImmune, duration.immuneCooldown);
                    window.clear();
                    board.draw(window);
                    window.display();
                }
            }
        }
        window.clear();
        board.draw(window);
        window.display();
    }

    return 0;
}
