#include "Platforma.h"


//platforma dodalem boola
Platforma::Platforma(float x, float y, float szerokosc) : Obiekt(x, y), czyDotknieta(false) {
    ksztalt.setSize(sf::Vector2f(szerokosc, 20.f));
    ksztalt.setFillColor(sf::Color(255, 0, 255)); // Jasny neonowy róż
    ksztalt.setPosition(pozycja);
}




void Platforma::aktualizuj(float deltaTime) {

}

void Platforma::rysuj(sf::RenderWindow& okno) {
    okno.draw(ksztalt);
}

sf::FloatRect Platforma::pobierzGranice() const {
    return ksztalt.getGlobalBounds();
}


//dotknieta platforma
void Platforma::oznaczJakoDotknieta() {
    czyDotknieta = true;
    ksztalt.setFillColor(sf::Color(100, 0, 100)); //ciemny roz
}