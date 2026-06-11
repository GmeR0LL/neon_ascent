#ifndef GRA_H
#define GRA_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random> // Wymóg: nowożytne losowanie w C++
#include "Obiekt.h"

class Gra {
private:
    sf::RenderWindow okno;
    sf::View kamera; // Wirtualna kamera śledząca gracza

    std::vector<std::unique_ptr<Obiekt>> obiektyWGrze;

    // Zmienne do generowania mapy w locie
    float najwyzszaPlatformaY;
    std::mt19937 generatorRNG;
    std::uniform_real_distribution<float> rozkladX;

    void obsluzZdarzenia();
    void aktualizuj(float deltaTime);
    void rysuj();

    // Nowe funkcje
    void generujPlatformy();
    void usunStarePlatformy();

public:
    Gra();
    void uruchom();
};

#endif // GRA_H