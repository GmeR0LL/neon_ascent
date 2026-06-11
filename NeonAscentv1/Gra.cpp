#include "Gra.h"

Gra::Gra() : okno(sf::VideoMode(800, 600), "Neon Ascent - v1") {
    okno.setFramerateLimit(60);
}

void Gra::uruchom() {
    sf::Clock zegar;
    while (okno.isOpen()) {
        float deltaTime = zegar.restart().asSeconds();
        obsluzZdarzenia();
        aktualizuj(deltaTime);
        rysuj();
    }
}

void Gra::obsluzZdarzenia() {
    sf::Event zdarzenie;
    while (okno.pollEvent(zdarzenie)) {
        if (zdarzenie.type == sf::Event::Closed)
            okno.close();
    }
}

void Gra::aktualizuj(float deltaTime) {
    for (auto& obiekt : obiektyWGrze) {
        obiekt->aktualizuj(deltaTime);
    }
}

void Gra::rysuj() {
    okno.clear(sf::Color(15, 15, 30));

    for (auto& obiekt : obiektyWGrze) {
        obiekt->rysuj(okno);
    }

    okno.display();
}