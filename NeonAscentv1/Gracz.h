#ifndef GRACZ_H
#define GRACZ_H

#include "Obiekt.h"
#include <vector>

class Gracz : public Obiekt {
private:
    sf::RectangleShape ksztalt;
    std::vector<sf::Texture> teksturyAnimacji;
    std::vector<sf::IntRect> prostokatyAnimacji;
    sf::Sprite slime;
    int obecnaKlatka;
    float czasAnimacji;
    float czasKlatki;
    bool animacjaSkokuAktywna;
    bool patrzyWLewo;
    bool efektLadowaniaAktywny;
    float czasEfektuLadowania;
    bool poprzedniPrzyciskSkoku;
    int mana;
    float szybkoscRuchu;
    float grawitacja;
    float silaSkoku;

public:
    Gracz(float x, float y);
    void aktualizuj(float deltaTime) override;
    void rysuj(sf::RenderWindow& okno) override;
    sf::FloatRect pobierzGranice() const override;
    void skok();
    void superSkok();
    void rozpoczynijAnimacjeSkoku();
    void rozpoczynijEfektLadowania();
    void odnawijMane();
    int pobierzMane() const { return mana; }
    float pobierzPredkoscY() const { return predkosc.y; }
};

#endif // GRACZ_H
