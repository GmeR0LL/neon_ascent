#ifndef PLATFORMA_H
#define PLATFORMA_H

#include "Obiekt.h"

class Platforma : public Obiekt {
private:
    sf::RectangleShape ksztalt;

public:
    Platforma(float x, float y, float szerokosc);
    void aktualizuj(float deltaTime) override;
    void rysuj(sf::RenderWindow& okno) override;
    sf::FloatRect pobierzGranice() const override;
};

#endif // PLATFORMA_H