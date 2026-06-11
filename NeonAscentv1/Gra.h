#ifndef GRA_H
#define GRA_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random>
#include "Obiekt.h"

class Gra {
private:
    sf::RenderWindow okno;
    sf::View kamera;

    std::vector<std::unique_ptr<Obiekt>> obiektyWGrze;

    //zmienne do mapy
    float najwyzszaPlatformaY;
    std::mt19937 generatorRNG;
    std::uniform_real_distribution<float> rozkladX;

    int obecnyWynik;

    void obsluzZdarzenia();
    void aktualizuj(float deltaTime);
    void rysuj();

    //potrzebne funkcje
    void generujPlatformy();
    void usunStarePlatformy();
    void zapiszWynik();

public:
    Gra();
    void uruchom();
};

#endif // GRA_H