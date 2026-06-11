#include "Gracz.h"

Gracz::Gracz(float x, float y) : Obiekt(x, y) {
    ksztalt.setSize(sf::Vector2f(30.f, 30.f));
    ksztalt.setFillColor(sf::Color::Cyan);
    ksztalt.setPosition(pozycja);

    szybkoscRuchu = 400.f;
    grawitacja = 1200.f;  // Ciągnie w dół (oś Y rośnie w dół w SFML)
    silaSkoku = -750.f;   // Wybija do góry
}

void Gracz::aktualizuj(float deltaTime) {
    // 1. Grawitacja - wektor przyspieszenia
    predkosc.y += grawitacja * deltaTime;

    // 2. Sterowanie
    predkosc.x = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        predkosc.x = -szybkoscRuchu;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        predkosc.x = szybkoscRuchu;
    }

    // 3. Aktualizacja pozycji o wektor prędkości
    pozycja += predkosc * deltaTime;

    // 4. Zawijanie ekranu
    if (pozycja.x < 0) pozycja.x = 800.f;
    if (pozycja.x > 800) pozycja.x = 0.f;

    ksztalt.setPosition(pozycja);
}

void Gracz::skok() {
    predkosc.y = silaSkoku;
}

void Gracz::rysuj(sf::RenderWindow& okno) {
    okno.draw(ksztalt);
}

sf::FloatRect Gracz::pobierzGranice() const {
    return ksztalt.getGlobalBounds();
}