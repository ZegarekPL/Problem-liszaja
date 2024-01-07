#include "Menu.h"
#include "Board.h"

void Menu::drawMenu(sf::RenderWindow& window) {
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
    title = sf::Text("Menu", font, 30);
    sf::FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
    title.setPosition(sf::Vector2f(640.0f, 50.0f));
    window.draw(title);

    // Dodanie rund
    drawButton(window, "+10", sf::Vector2f(40.0f, 100.0f), [this]() { increase(10, "size"); }, sf::Color(0, 0, 255), sf::Color(102, 0, 204));
    drawButton(window, "+5", sf::Vector2f(40.0f, 150.0f), [this]() { increase(5, "size"); }, sf::Color(0, 204, 0), sf::Color(0, 204, 102));
    drawButton(window, "+1", sf::Vector2f(40.0f, 200.0f), [this]() { increase(1, "size"); }, sf::Color(204, 0, 0), sf::Color(204, 102, 0));

    sf::Text sizeText("Ilosc pol: " + std::to_string(menuSize), font, 20);
    sizeText.setPosition(sf::Vector2f(40.0f, 250.0f));
    window.draw(sizeText);

    drawButton(window, "-1", sf::Vector2f(40.0f, 300.0f), [this]() { decrease(1, "size"); }, sf::Color(204, 0, 0), sf::Color(204, 102, 0));
    drawButton(window, "-5", sf::Vector2f(40.0f, 350.0f), [this]() { decrease(5, "size"); }, sf::Color(0, 204, 0), sf::Color(0, 204, 102));
    drawButton(window, "-10", sf::Vector2f(40.0f, 400.0f), [this]() { decrease(10, "size"); }, sf::Color(0, 0, 255), sf::Color(102, 0, 204));

    // Dodanie rund
    drawButton(window, "+10", sf::Vector2f(240.0f, 100.0f), [this]() { increase(10, "maxround"); }, sf::Color(0, 0, 255), sf::Color(102, 0, 204));
    drawButton(window, "+5", sf::Vector2f(240.0f, 150.0f), [this]() { increase(5, "maxround"); }, sf::Color(0, 204, 0), sf::Color(0, 204, 102));
    drawButton(window, "+1", sf::Vector2f(240.0f, 200.0f), [this]() { increase(1, "maxround"); }, sf::Color(204, 0, 0), sf::Color(204, 102, 0));

    sf::Text roundsText("Ilosc rund: " + std::to_string(menuMaxround), font, 20);
    roundsText.setPosition(sf::Vector2f(240.0f, 250.0f));
    window.draw(roundsText);

    drawButton(window, "-1", sf::Vector2f(240.0f, 300.0f), [this]() { decrease(1, "maxround"); }, sf::Color(204, 0, 0), sf::Color(204, 102, 0));
    drawButton(window, "-5", sf::Vector2f(240.0f, 350.0f), [this]() { decrease(5, "maxround"); }, sf::Color(0, 204, 0), sf::Color(0, 204, 102));
    drawButton(window, "-10", sf::Vector2f(240.0f, 400.0f), [this]() { decrease(10, "maxround"); }, sf::Color(0, 0, 255), sf::Color(102, 0, 204));

    // Dodanie Przerwy
    drawButton(window, "+10", sf::Vector2f(440.0f, 100.0f), [this]() { increase(10, "holdprocess"); }, sf::Color(0, 0, 255), sf::Color(102, 0, 204));
    drawButton(window, "+5", sf::Vector2f(440.0f, 150.0f), [this]() { increase(5, "holdprocess"); }, sf::Color(0, 204, 0), sf::Color(0, 204, 102));
    drawButton(window, "+1", sf::Vector2f(440.0f, 200.0f), [this]() { increase(1, "holdprocess"); }, sf::Color(204, 0, 0), sf::Color(204, 102, 0));

    sf::Text holdprocessText("Przerwa: " + std::to_string(menuHoldprocess), font, 20);
    holdprocessText.setPosition(sf::Vector2f(440.0f, 250.0f));
    window.draw(holdprocessText);

    drawButton(window, "-1", sf::Vector2f(440.0f, 300.0f), [this]() { decrease(1, "holdprocess"); }, sf::Color(204, 0, 0), sf::Color(204, 102, 0));
    drawButton(window, "-5", sf::Vector2f(440.0f, 350.0f), [this]() { decrease(5, "holdprocess"); }, sf::Color(0, 204, 0), sf::Color(0, 204, 102));
    drawButton(window, "-10", sf::Vector2f(440.0f, 400.0f), [this]() { decrease(10, "holdprocess"); }, sf::Color(0, 0, 255), sf::Color(102, 0, 204));

    // Dodanie Procentu
    drawButton(window, "+10", sf::Vector2f(640.0f, 100.0f), [this]() { increase(10, "infectionPercent"); }, sf::Color(0, 0, 255), sf::Color(102, 0, 204));
    drawButton(window, "+5", sf::Vector2f(640.0f, 150.0f), [this]() { increase(5, "infectionPercent"); }, sf::Color(0, 204, 0), sf::Color(0, 204, 102));
    drawButton(window, "+1", sf::Vector2f(640.0f, 200.0f), [this]() { increase(1, "infectionPercent"); }, sf::Color(204, 0, 0), sf::Color(204, 102, 0));

    sf::Text infectionPercentText("% szansy: " + std::to_string(menuInfectionPercent), font, 20);
    infectionPercentText.setPosition(sf::Vector2f(640.0f, 250.0f));
    window.draw(infectionPercentText);

    drawButton(window, "-1", sf::Vector2f(640.0f, 300.0f), [this]() { decrease(1, "infectionPercent"); }, sf::Color(204, 0, 0), sf::Color(204, 102, 0));
    drawButton(window, "-5", sf::Vector2f(640.0f, 350.0f), [this]() { decrease(5, "infectionPercent"); }, sf::Color(0, 204, 0), sf::Color(0, 204, 102));
    drawButton(window, "-10", sf::Vector2f(640.0f, 400.0f), [this]() { decrease(10, "infectionPercent"); }, sf::Color(0, 0, 255), sf::Color(102, 0, 204));

    // Dodanie Czasu miêdzy Infected a Immune
    drawButton(window, "+10", sf::Vector2f(840.0f, 100.0f), [this]() { increase(10, "infectedToImmune"); }, sf::Color(0, 0, 255), sf::Color(102, 0, 204));
    drawButton(window, "+5", sf::Vector2f(840.0f, 150.0f), [this]() { increase(5, "infectedToImmune"); }, sf::Color(0, 204, 0), sf::Color(0, 204, 102));
    drawButton(window, "+1", sf::Vector2f(840.0f, 200.0f), [this]() { increase(1, "infectedToImmune"); }, sf::Color(204, 0, 0), sf::Color(204, 102, 0));

    sf::Text infectedToImmuneText("Inf 2 Imm: " + std::to_string(menuInfectedToImmune), font, 20);
    infectedToImmuneText.setPosition(sf::Vector2f(840.0f, 250.0f));
    window.draw(infectedToImmuneText);

    drawButton(window, "-1", sf::Vector2f(840.0f, 300.0f), [this]() { decrease(1, "infectedToImmune"); }, sf::Color(204, 0, 0), sf::Color(204, 102, 0));
    drawButton(window, "-5", sf::Vector2f(840.0f, 350.0f), [this]() { decrease(5, "infectedToImmune"); }, sf::Color(0, 204, 0), sf::Color(0, 204, 102));
    drawButton(window, "-10", sf::Vector2f(840.0f, 400.0f), [this]() { decrease(10, "infectedToImmune"); }, sf::Color(0, 0, 255), sf::Color(102, 0, 204));

    // Dodanie immuneCooldown
    drawButton(window, "+10", sf::Vector2f(1040.0f, 100.0f), [this]() { increase(10, "immuneCooldown"); }, sf::Color(0, 0, 255), sf::Color(102, 0, 204));
    drawButton(window, "+5", sf::Vector2f(1040.0f, 150.0f), [this]() { increase(5, "immuneCooldown"); }, sf::Color(0, 204, 0), sf::Color(0, 204, 102));
    drawButton(window, "+1", sf::Vector2f(1040.0f, 200.0f), [this]() { increase(1, "immuneCooldown"); }, sf::Color(204, 0, 0), sf::Color(204, 102, 0));

    sf::Text immuneCooldownText("Imm 2 Heal: " + std::to_string(menuImmuneCooldown), font, 20);
    immuneCooldownText.setPosition(sf::Vector2f(1040.0f, 250.0f));
    window.draw(immuneCooldownText);

    drawButton(window, "-1", sf::Vector2f(1040.0f, 300.0f), [this]() { decrease(1, "immuneCooldown"); }, sf::Color(204, 0, 0), sf::Color(204, 102, 0));
    drawButton(window, "-5", sf::Vector2f(1040.0f, 350.0f), [this]() { decrease(5, "immuneCooldown"); }, sf::Color(0, 204, 0), sf::Color(0, 204, 102));
    drawButton(window, "-10", sf::Vector2f(1040.0f, 400.0f), [this]() { decrease(10, "immuneCooldown"); }, sf::Color(0, 0, 255), sf::Color(102, 0, 204));


    // Dodanie napisu
    exit = sf::Text("Aby wyjsc nacisnij: w", font, 25);
    sf::FloatRect exitRect = exit.getLocalBounds();
    exit.setOrigin(exitRect.left + exitRect.width / 2.0f, exitRect.top + exitRect.height / 2.0f);
    exit.setPosition(sf::Vector2f(640.0f, 600.0f));
    window.draw(exit);
}

void Menu::drawButton(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, const std::function<void()>& onClick, const sf::Color& mainColor, const sf::Color& hoverColor) {
    sf::RectangleShape button(sf::Vector2f(120.0f, 35.0f));
    button.setFillColor(mainColor);  // Use mainColor as the initial fill color
    button.setPosition(position);

    if (!font.loadFromFile("Inter-Medium.ttf")) {
        std::cout << "Error: B³¹d ³adowania czcionki" << std::endl;
        return;
    }

    buttonText = sf::Text(text, font, 20);
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    buttonText.setPosition(position.x + button.getSize().x / 2.0f, position.y + button.getSize().y / 2.0f);

    if (button.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
        button.setFillColor(hoverColor);  // Use hoverColor if the mouse is over the button
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            onClick();
        }
    }

    window.draw(button);
    window.draw(buttonText);
}



void Menu::increase(int howMuch, const std::string& variable) {
    if (variable == "size") {
        menuSize += howMuch;
    }
    if (variable == "maxround") {
        menuMaxround += howMuch;
    }
    if (variable == "holdprocess") {
        menuHoldprocess += howMuch;
    }
    if (variable == "infectionPercent") {
        menuInfectionPercent += howMuch;
    }
    if (variable == "infectedToImmune") {
        menuInfectedToImmune += howMuch;
    }
    if (variable == "immuneCooldown") {
        menuImmuneCooldown += howMuch;
    }
}

void Menu::decrease(int howMuch, const std::string& variable) {
    if (menuSize > 1 && variable == "size") {
        menuSize -= howMuch;
    }
    if (menuMaxround > 1 && variable == "maxround") {
        menuMaxround -= howMuch;
    }
    if (menuHoldprocess > 1 && variable == "holdprocess") {
        menuHoldprocess -= howMuch;;
    }
    if (menuInfectionPercent > 1 && variable == "infectionPercent") {
        menuInfectionPercent -= howMuch;
    }
    if (menuInfectedToImmune > 1 && variable == "infectedToImmune") {
        menuInfectedToImmune -= howMuch;
    }
    if (menuImmuneCooldown > 1 && variable == "immuneCooldown") {
        menuImmuneCooldown -= howMuch;
    }
}