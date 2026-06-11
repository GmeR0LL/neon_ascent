#ifndef GRA_H
#define GRA_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Obiekt.h" // Wrzucamy nasz polski Obiekt

class Gra {
private:
    sf::RenderWindow okno;

    // Główny kontener na wskaźniki inteligentne
    std::vector<std::unique_ptr<Obiekt>> obiektyWGrze;

    void obsluzZdarzenia();
    void aktualizuj(float deltaTime);
    void rysuj();

public:
    Gra();
    void uruchom();
};

#endif // GRA_H
