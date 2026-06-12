#ifndef BONUS_H
#define BONUS_H

#include "Obiekt.h"

class Bonus : public Obiekt {
private:
    sf::CircleShape ksztalt;
    bool zebrany;
public:
    Bonus(float x, float y);
    void aktualizuj(float deltaTime) override;
    void rysuj(sf::RenderWindow& okno) override;
    sf::FloatRect pobierzGranice() const override;

    bool czyZebrany() const { return zebrany; }
    void zbierz() { zebrany = true; }
};

#endif // BONUS_H
