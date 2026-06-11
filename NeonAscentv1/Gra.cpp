#include "Gra.h"
#include "Gracz.h"
#include "Platforma.h"
#include <algorithm>

Gra::Gra() : okno(sf::VideoMode(800, 600), "Neon Ascent - v4") {
    okno.setFramerateLimit(60);

    // Konfiguracja kamery
    kamera.setSize(800.f, 600.f);
    kamera.setCenter(400.f, 300.f);

    //generator
    std::random_device rd;
    generatorRNG.seed(rd());
    rozkladX = std::uniform_real_distribution<float>(50.f, 600.f);
    obecnyWynik = 0;

    //gracz
    obiektyWGrze.push_back(std::make_unique<Gracz>(400.f, 200.f));

    // Start podloga
    najwyzszaPlatformaY = 400.f;
    obiektyWGrze.push_back(std::make_unique<Platforma>(0.f, 550.f, 800.f));


    //pierwsza platforma 100% mozliwa do skoku
    obiektyWGrze.push_back(std::make_unique<Platforma>(350.f, 400.f, 100.f));
    najwyzszaPlatformaY = 400.f;

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
        //ruch kamery
        if (gracz->pobierzPozycje().y < kamera.getCenter().y) {
            kamera.setCenter(400.f, gracz->pobierzPozycje().y);
        }

        //gameover i zapis wyniku

        if (gracz->pobierzPozycje().y > kamera.getCenter().y + 300.f) {
            zapiszWynik();
            okno.close();

        }

        //kolizja
        if (gracz->pobierzPredkoscY() > 0) {
            sf::FloatRect graniceGracza = gracz->pobierzGranice();
            for (auto& obiekt : obiektyWGrze) {
                if (Platforma* platforma = dynamic_cast<Platforma*>(obiekt.get())) {
                    if (graniceGracza.intersects(platforma->pobierzGranice())) {
                        if (graniceGracza.top + graniceGracza.height - 20.f < platforma->pobierzGranice().top) {
                            gracz->skok();
                            if (!platforma->bylaDotknieta()) { //dodawanie punktu
                                platforma->oznaczJakoDotknieta();
                                obecnyWynik++;
                            }
                        }
                    }
                }
            }
        }
    }

    //dynamik map
    generujPlatformy();
    usunStarePlatformy();
}

void Gra::rysuj() {
    okno.clear(sf::Color(15, 15, 30));

    okno.setView(kamera);

    for (auto& obiekt : obiektyWGrze) {
        obiekt->rysuj(okno);
    }

    okno.display();
}

//tworzenie dynamicznej platformy
void Gra::generujPlatformy() {
 //jezeli wysoko to generuje platforme
    while (najwyzszaPlatformaY > kamera.getCenter().y - 600.f) {
        najwyzszaPlatformaY -= 140.f; // Skok w górę między platformami //90 na 140 aby zwiekszyc przerwe
        float losowyX = rozkladX(generatorRNG);

        // platformy
        obiektyWGrze.push_back(std::make_unique<Platforma>(losowyX, najwyzszaPlatformaY, 120.f));
    }
}

//optymalizacja pamieci
void Gra::usunStarePlatformy() {
    float dolEkranu = kamera.getCenter().y + 400.f;
    obiektyWGrze.erase(std::remove_if(obiektyWGrze.begin(), obiektyWGrze.end(),
                                      [dolEkranu](const std::unique_ptr<Obiekt>& obj) {
                                          //platforma, jezeli jest ponizej ekranu to
                                          if (dynamic_cast<Platforma*>(obj.get())) {
                                              return obj->pobierzPozycje().y > dolEkranu;
                                          }
                                          return false;
                                      }), obiektyWGrze.end());
}



void Gra::zapiszWynik() {
    std::ofstream plik("wyniki.txt", std::ios::app);


    if (plik.is_open()) {
        plik << "Wynik gracza: " << obecnyWynik << "\n";
        plik.close();
    }
}