#include "Gra.h"
#include "Gracz.h"
#include "Platforma.h"
#include <algorithm> // Dla std::remove_if

Gra::Gra() : okno(sf::VideoMode(800, 600), "Neon Ascent - v4") {
    okno.setFramerateLimit(60);

    // Konfiguracja kamery (rozmiar i środek)
    kamera.setSize(800.f, 600.f);
    kamera.setCenter(400.f, 300.f);

    // Inicjalizacja generatora (pozycje X od 50 do 600)
    std::random_device rd;
    generatorRNG.seed(rd());
    rozkladX = std::uniform_real_distribution<float>(50.f, 600.f);

    // Gracz
    obiektyWGrze.push_back(std::make_unique<Gracz>(400.f, 200.f));

    // Startowa, długa podłoga
    najwyzszaPlatformaY = 400.f;
    obiektyWGrze.push_back(std::make_unique<Platforma>(0.f, 550.f, 800.f));

    // Wygenerowanie pierwszych platform na start
    generujPlatformy();
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

    Gracz* gracz = nullptr;
    for (auto& obiekt : obiektyWGrze) {
        if (auto g = dynamic_cast<Gracz*>(obiekt.get())) {
            gracz = g;
            break;
        }
    }

    if (gracz) {
        // --- 1. RUCH KAMERY ---
        // Jeśli gracz jest wyżej (ma mniejszy Y) niż środek kamery, przesuwamy kamerę za nim.
        if (gracz->pobierzPozycje().y < kamera.getCenter().y) {
            kamera.setCenter(400.f, gracz->pobierzPozycje().y);
        }

        // --- 2. KOLIZJE ---
        if (gracz->pobierzPredkoscY() > 0) {
            sf::FloatRect graniceGracza = gracz->pobierzGranice();
            for (auto& obiekt : obiektyWGrze) {
                if (Platforma* platforma = dynamic_cast<Platforma*>(obiekt.get())) {
                    if (graniceGracza.intersects(platforma->pobierzGranice())) {
                        if (graniceGracza.top + graniceGracza.height - 20.f < platforma->pobierzGranice().top) {
                            gracz->skok();
                        }
                    }
                }
            }
        }
    }

    // --- 3. DYNAMICZNA MAPA ---
    generujPlatformy();
    usunStarePlatformy();
}

void Gra::rysuj() {
    okno.clear(sf::Color(15, 15, 30));

    // Kluczowe: Mówimy oknu, żeby patrzyło przez naszą przesuwaną kamerę!
    okno.setView(kamera);

    for (auto& obiekt : obiektyWGrze) {
        obiekt->rysuj(okno);
    }

    okno.display();
}

// Tworzy platformy wyżej, jeśli zbliżamy się do górnej krawędzi kamery
void Gra::generujPlatformy() {
    // Generuj dopóki najwyższa platforma nie jest sporo powyżej obecnego widoku
    while (najwyzszaPlatformaY > kamera.getCenter().y - 600.f) {
        najwyzszaPlatformaY -= 90.f; // Skok w górę między platformami
        float losowyX = rozkladX(generatorRNG);

        // Zwykłe, mniejsze platformy (szerokość 120)
        obiektyWGrze.push_back(std::make_unique<Platforma>(losowyX, najwyzszaPlatformaY, 120.f));
    }
}

// Usuwa platformy, które zniknęły daleko w dole pod kamerą (Optymalizacja pamięci)
void Gra::usunStarePlatformy() {
    float dolEkranu = kamera.getCenter().y + 400.f;

    // Idiom Erase-Remove (bardzo dobrze punktowane przez wykładowców)
    obiektyWGrze.erase(std::remove_if(obiektyWGrze.begin(), obiektyWGrze.end(),
                                      [dolEkranu](const std::unique_ptr<Obiekt>& obj) {
                                          // Sprawdzamy czy to platforma i czy wypadła poza dół
                                          if (dynamic_cast<Platforma*>(obj.get())) {
                                              return obj->pobierzPozycje().y > dolEkranu;
                                          }
                                          return false;
                                      }), obiektyWGrze.end());
}