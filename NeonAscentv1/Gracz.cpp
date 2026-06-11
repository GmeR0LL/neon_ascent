#include "Gracz.h"

Gracz::Gracz(float x, float y) : Obiekt(x, y) {
    ksztalt.setSize(sf::Vector2f(30.f, 30.f));
    ksztalt.setFillColor(sf::Color::Cyan); // Nasz neonowy kwadracik
    ksztalt.setPosition(pozycja);

    szybkoscRuchu = 400.f; // piksele na sekundę
}

void Gracz::aktualizuj(float deltaTime) {
    predkosc.x = 0.f;

    // Sterowanie (A/D lub Strzałki)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        predkosc.x = -szybkoscRuchu;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        predkosc.x = szybkoscRuchu;
    }

    // Aplikowanie prędkości poziomej do pozycji (wektory w praktyce)
    pozycja.x += predkosc.x * deltaTime;

    // Zawijanie ekranu (jak w Icy Tower)
    if (pozycja.x < 0) pozycja.x = 800.f;
    if (pozycja.x > 800) pozycja.x = 0.f;

    ksztalt.setPosition(pozycja);
}

void Gracz::rysuj(sf::RenderWindow& okno) {
    okno.draw(ksztalt);
}

sf::FloatRect Gracz::pobierzGranice() const {
    return ksztalt.getGlobalBounds();
}