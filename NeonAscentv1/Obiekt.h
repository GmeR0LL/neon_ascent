#ifndef OBIEKT_H
#define OBIEKT_H

#include <SFML/Graphics.hpp>

class Obiekt
{
protected:
    sf::Vector2f pozycja;
    sf::Vector2f predkosc;
public:
    Obiekt(float x, float y) : pozycja(x, y), predkosc(0.f, 0.f) {}
    virtual ~Obiekt() = default;

    //funkcje void polimorfizm
    virtual void aktualizuj(float deltaTime) = 0;
    virtual void rysuj(sf::RenderWindow& okno) = 0;
    virtual sf::FloatRect pobierzGranice() const = 0;

    sf::Vector2f pobierzPozycje() const { return pozycja; }
};

#endif // OBIEKT_H
