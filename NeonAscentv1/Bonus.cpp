#include "Bonus.h"

Bonus::Bonus(float x, float y) : Obiekt(x, y), zebrany(false) {
    ksztalt.setRadius(15.f);
    ksztalt.setFillColor(sf::Color::Yellow);
    ksztalt.setPosition(pozycja);
}

void Bonus::aktualizuj(float deltaTime) {
//na razie stoi w  miejscu
}

void Bonus::rysuj(sf::RenderWindow& okno) {
    if (!zebrany) {
        okno.draw(ksztalt);
    }
}

sf::FloatRect Bonus::pobierzGranice() const {
    return ksztalt.getGlobalBounds();
}