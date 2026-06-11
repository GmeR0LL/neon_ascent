#ifndef GRACZ_H
#define GRACZ_H

#include "Obiekt.h"

class Gracz : public Obiekt {
private:
    sf::RectangleShape ksztalt;
    float szybkoscRuchu;
    float grawitacja;
    float silaSkoku;

public:
    Gracz(float x, float y);
    void aktualizuj(float deltaTime) override;
    void rysuj(sf::RenderWindow& okno) override;
    sf::FloatRect pobierzGranice() const override;
    void skok();
    float pobierzPredkoscY() const { return predkosc.y; }
};

#endif // GRACZ_H
