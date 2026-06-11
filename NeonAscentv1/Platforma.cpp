#include "Platforma.h"

Platforma::Platforma(float x, float y, float szerokosc) : Obiekt(x, y) {
    ksztalt.setSize(sf::Vector2f(szerokosc, 20.f));
    ksztalt.setFillColor(sf::Color(255, 0, 255)); //platforma
    ksztalt.setPosition(pozycja);
}

void Platforma::aktualizuj(float deltaTime) {
//co ja tu mam zrobic?
}

void Platforma::rysuj(sf::RenderWindow& okno) {
    okno.draw(ksztalt);
}

sf::FloatRect Platforma::pobierzGranice() const {
    return ksztalt.getGlobalBounds();
}