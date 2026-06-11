#include "Platforma.h"

Platforma::Platforma(float x, float y, float szerokosc) : Obiekt(x, y) {
    ksztalt.setSize(sf::Vector2f(szerokosc, 20.f));
    ksztalt.setFillColor(sf::Color(255, 0, 255)); // Różowa platforma
    ksztalt.setPosition(pozycja);
}

void Platforma::aktualizuj(float deltaTime) {
    // Platformy statyczne na razie nie robią nic w update
}

void Platforma::rysuj(sf::RenderWindow& okno) {
    okno.draw(ksztalt);
}

sf::FloatRect Platforma::pobierzGranice() const {
    return ksztalt.getGlobalBounds();
}