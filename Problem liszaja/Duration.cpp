#include "Duration.h"

Duration::Duration() {
    maxround = 1;
}

void Duration::delay(int time, sf::RenderWindow& window) {
    sf::Clock delayClock;
    delayClock.restart();
    time *= 1000;
    while (delayClock.getElapsedTime().asMilliseconds() < time) { }
}

void Duration::consoleStart() {
    do {
        std::cout << "Wpisz ilosc rund symulacji: ";
        std::cin >> maxround;

        if (maxround <= 0) {
            std::cout << "Error: Cant be less than 0 or 0." << std::endl;
        }
    } while (maxround <= 0);
    do {
        std::cout << "Wpisz czas miedzy krokami symulacji: ";
        std::cin >> holdprocess;

        if (holdprocess <= 0 || holdprocess > 60) {
            std::cout << "Error: Too much time for holdprocess." << std::endl;
        }

    } while (holdprocess <= 0 || holdprocess > 60);
    do {
        std::cout << "Wpisz szanse zarazenia (wpisuj¹c np. 0.8 = 80%): ";
        std::cin >> infectionPercent;

        if (infectionPercent < 0 || infectionPercent > 1) {
            std::cout << "Error: Too much percent of infection." << std::endl;
        }

    } while (infectionPercent < 0 || infectionPercent > 1);
    do {
        std::cout << "Wpisz po ilu rundach komorka zmienia status z Infected na Immune: ";
        std::cin >> infectedToImmune;

        if (infectedToImmune <= 0) {
            std::cout << "Error: Cant be less than 0." << std::endl;
        }

    } while (infectedToImmune <= 0);
    do {
        std::cout << "Wpisz po ilu rundach komorka pozostanie Immune: ";
        std::cin >> immuneCooldown;

        if (immuneCooldown <= 0) {
            std::cout << "Error: Cant be less than 0." << std::endl;
        }
    } while (immuneCooldown <= 0);
}


void Duration::drawMenu(sf::RenderWindow& window) {
    // Dodawanie czcionki
    if (!font.loadFromFile("Inter-Medium.ttf")) {
        std::cout << "Error: B³¹d ³adowania czcionki" << std::endl;
        return;
    }

    // Dodanie napisu
    title = sf::Text("Problem liszaja", font, 30);
    sf::FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
    title.setPosition(sf::Vector2f(400.0f, 50.0f));
    window.draw(title);

    // Dodanie przycisków
    drawButton(window, "Zwieksz", sf::Vector2f(400.0f, 150.0f), [this]() { increase(); });
    drawButton(window, "Zmniejsz", sf::Vector2f(400.0f, 250.0f), [this]() { decrease(); });

    // Wyœwietlanie aktualnej iloœci rund
    sf::Text roundsText("Ilosc rund: " + std::to_string(maxround), font, 20);
    roundsText.setPosition(sf::Vector2f(400.0f, 350.0f));
    window.draw(roundsText);
}

void Duration::drawButton(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, const std::function<void()>& onClick) {
    sf::RectangleShape button(sf::Vector2f(150.0f, 50.0f));
    button.setFillColor(sf::Color::Blue);
    button.setPosition(position);

    if (!font.loadFromFile("Inter-Medium.ttf")) {
        std::cout << "Error: B³¹d ³adowania czcionki" << std::endl;
        return;
    }

    buttonText = sf::Text(text, font, 30);
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


void Duration::increase() {
    maxround++;
}

// Metoda do zmniejszania iloœci rund (nie spada poni¿ej 1)
void Duration::decrease() {
    if (maxround > 1) {
        maxround--;
    }
}