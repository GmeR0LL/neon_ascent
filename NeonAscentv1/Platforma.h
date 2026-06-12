#ifndef PLATFORMA_H
#define PLATFORMA_H

#include "Obiekt.h"

enum class TypPlatformy { ZWYKLA, KRUCHA, MIGAJACA};
class Platforma : public Obiekt {
private:
    sf::RectangleShape ksztalt;
    bool czyDotknieta;

    TypPlatformy typ;
    float zegarMigotania;
    bool widoczna,
        bool zniszczona;

public:
    Platforma(float x, float y, float szerokosc, TypPlatformy typPlatformy = TypPlatformy::ZWYKLA);
    void aktualizuj(float deltaTime) override;
    void rysuj(sf::RenderWindow& okno) override;
    sf::FloatRect pobierzGranice() const override;

    bool bylaDotknieta() const { return czyDotknieta; }
    void oznaczJakoDotknieta();

    bool czyAktywna() const;
};

#endif // PLATFORMA_H