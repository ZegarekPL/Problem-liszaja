#include "Menu.h"

Menu::Menu() {
    duration.maxround = 1;
}

void Menu::drawMenu(sf::RenderWindow& window) {
    // Dodawanie czcionki
    if (!font.loadFromFile("Inter-Medium.ttf")) {
        std::cout << "Error: B³¹d ³adowania czcionki" << std::endl;
        return;
    }

    // Dodanie napisu
    title = sf::Text("Menu", font, 30);
    sf::FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
    title.setPosition(sf::Vector2f(640.0f, 50.0f));
    window.draw(title);

    // Dodanie rund
    drawButton(window, "+10", sf::Vector2f(40.0f, 100.0f), [this]() { increase(10); });
    drawButton(window, "+5", sf::Vector2f(40.0f, 150.0f), [this]() { increase(5); });
    drawButton(window, "+1", sf::Vector2f(40.0f, 200.0f), [this]() { increase(1); });

    sf::Text sizeText("Ilosc pol: " + std::to_string(board.size), font, 20);
    sizeText.setPosition(sf::Vector2f(40.0f, 250.0f));
    window.draw(sizeText);

    drawButton(window, "-1", sf::Vector2f(40.0f, 300.0f), [this]() { decrease(1); });
    drawButton(window, "-5", sf::Vector2f(40.0f, 350.0f), [this]() { decrease(5); });
    drawButton(window, "-10", sf::Vector2f(40.0f, 400.0f), [this]() { decrease(10); });

    // Dodanie rund
    drawButton(window, "+10", sf::Vector2f(240.0f, 100.0f), [this]() { increase(10); });
    drawButton(window, "+5", sf::Vector2f(240.0f, 150.0f), [this]() { increase(5); });
    drawButton(window, "+1", sf::Vector2f(240.0f, 200.0f), [this]() { increase(1); });

    sf::Text roundsText("Ilosc rund: " + std::to_string(duration.maxround), font, 20);
    roundsText.setPosition(sf::Vector2f(240.0f, 250.0f));
    window.draw(roundsText);

    drawButton(window, "-1", sf::Vector2f(240.0f, 300.0f), [this]() { decrease(1); });
    drawButton(window, "-5", sf::Vector2f(240.0f, 350.0f), [this]() { decrease(5); });
    drawButton(window, "-10", sf::Vector2f(240.0f, 400.0f), [this]() { decrease(10); });

    // Dodanie Przerwy
    drawButton(window, "+10", sf::Vector2f(440.0f, 100.0f), [this]() { increase(10); });
    drawButton(window, "+5", sf::Vector2f(440.0f, 150.0f), [this]() { increase(5); });
    drawButton(window, "+1", sf::Vector2f(440.0f, 200.0f), [this]() { increase(1); });

    sf::Text holdprocessText("Przerwa: " + std::to_string(duration.holdprocess), font, 20);
    holdprocessText.setPosition(sf::Vector2f(440.0f, 250.0f));
    window.draw(holdprocessText);

    drawButton(window, "-1", sf::Vector2f(440.0f, 300.0f), [this]() { decrease(1); });
    drawButton(window, "-5", sf::Vector2f(440.0f, 350.0f), [this]() { decrease(5); });
    drawButton(window, "-10", sf::Vector2f(440.0f, 400.0f), [this]() { decrease(10); });

    // Dodanie Procentu
    drawButton(window, "+10", sf::Vector2f(640.0f, 100.0f), [this]() { increase(10); });
    drawButton(window, "+5", sf::Vector2f(640.0f, 150.0f), [this]() { increase(5); });
    drawButton(window, "+1", sf::Vector2f(640.0f, 200.0f), [this]() { increase(1); });

    sf::Text infectionPercentText("% zarazenia: " + std::to_string(duration.infectionPercent), font, 20);
    infectionPercentText.setPosition(sf::Vector2f(640.0f, 250.0f));
    window.draw(infectionPercentText);

    drawButton(window, "-1", sf::Vector2f(640.0f, 300.0f), [this]() { decrease(1); });
    drawButton(window, "-5", sf::Vector2f(640.0f, 350.0f), [this]() { decrease(5); });
    drawButton(window, "-10", sf::Vector2f(640.0f, 400.0f), [this]() { decrease(10); });

    // Dodanie Czasu miêdzy Infected a Immune
    drawButton(window, "+10", sf::Vector2f(840.0f, 100.0f), [this]() { increase(10); });
    drawButton(window, "+5", sf::Vector2f(840.0f, 150.0f), [this]() { increase(5); });
    drawButton(window, "+1", sf::Vector2f(840.0f, 200.0f), [this]() { increase(1); });

    sf::Text infectedToImmuneText("InfectedToImmune: " + std::to_string(duration.infectedToImmune), font, 20);
    infectedToImmuneText.setPosition(sf::Vector2f(840.0f, 250.0f));
    window.draw(infectedToImmuneText);

    drawButton(window, "-1", sf::Vector2f(840.0f, 300.0f), [this]() { decrease(1); });
    drawButton(window, "-5", sf::Vector2f(840.0f, 350.0f), [this]() { decrease(5); });
    drawButton(window, "-10", sf::Vector2f(840.0f, 400.0f), [this]() { decrease(10); });

    // Dodanie immuneCooldown
    drawButton(window, "+10", sf::Vector2f(1040.0f, 100.0f), [this]() { increase(10); });
    drawButton(window, "+5", sf::Vector2f(1040.0f, 150.0f), [this]() { increase(5); });
    drawButton(window, "+1", sf::Vector2f(1040.0f, 200.0f), [this]() { increase(1); });

    sf::Text immuneCooldownText("ImmuneCooldown: " + std::to_string(duration.immuneCooldown), font, 20);
    immuneCooldownText.setPosition(sf::Vector2f(1040.0f, 250.0f));
    window.draw(immuneCooldownText);

    drawButton(window, "-1", sf::Vector2f(1040.0f, 300.0f), [this]() { decrease(1); });
    drawButton(window, "-5", sf::Vector2f(1040.0f, 350.0f), [this]() { decrease(5); });
    drawButton(window, "-10", sf::Vector2f(1040.0f, 400.0f), [this]() { decrease(10); });
}

void Menu::drawButton(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, const std::function<void()>& onClick) {
    sf::RectangleShape button(sf::Vector2f(120.0f, 35.0f));
    button.setFillColor(sf::Color::Blue);
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
        button.setFillColor(sf::Color::Cyan);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            onClick();
        }
    }

    window.draw(button);
    window.draw(buttonText);
}


void Menu::increase(int howMuch) {
    duration.maxround += howMuch;
}

// Metoda do zmniejszania iloœci rund (nie spada poni¿ej 1)
void Menu::decrease(int howMuch) {
    if (duration.maxround > 1) {
        duration.maxround -= howMuch;
    }
}