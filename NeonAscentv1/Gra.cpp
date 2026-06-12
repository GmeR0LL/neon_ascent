#include "Bonus.h"
#include "Gra.h"
#include "Gracz.h"
#include "Platforma.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cmath>


Gra::Gra() : okno(sf::VideoMode(800, 600), "Neon Ascent") {
    okno.setFramerateLimit(60);
    obecnyStan = StanGry::MENU;

    //zaladowanie czcionki
    if (!czcionka.loadFromFile("media/czcionka.ttf")) {
        std::cout << "Blad ladowania czcionki. media/czcionka.ttf\n";
    }

    inicjalizujTlo();

    //generator
    std::random_device rd;
    generatorRNG.seed(rd());
    rozkladX = std::uniform_real_distribution<float>(50.f, 600.f);
    obecnyWynik = 0;

    //szykowanie ui
    inicjalizujMenu();
    inicjalizujGameOver();
    inicjalizujEkranWynikow();

    zresetujGre();
}

void Gra::inicjalizujTlo() {
    const char* sciezkaTla = "media/Background/Nebula Blue.png";
    if (!std::ifstream(sciezkaTla).good()) sciezkaTla = "../../media/Background/Nebula Blue.png";

    if (teksturaTla.loadFromFile(sciezkaTla)) {
        teksturaTla.setRepeated(true);
        tlo.setTexture(teksturaTla);
    }
    else {
        std::cout << "Blad ladowania tla: " << sciezkaTla << "\n";
    }

    const char* sciezkaGwiazdMalych = "media/Background/Stars Small_1.png";
    if (!std::ifstream(sciezkaGwiazdMalych).good()) sciezkaGwiazdMalych = "../../media/Background/Stars Small_1.png";

    if (teksturaGwiazdMalych.loadFromFile(sciezkaGwiazdMalych)) {
        teksturaGwiazdMalych.setRepeated(true);
        gwiazdyMale.setTexture(teksturaGwiazdMalych);
        gwiazdyMale.setColor(sf::Color(255, 255, 255, 170));
    }
    else {
        std::cout << "Blad ladowania tla: " << sciezkaGwiazdMalych << "\n";
    }

    const char* sciezkaGwiazdDuzych = "media/Background/Stars-Big_1_1_PC.png";
    if (!std::ifstream(sciezkaGwiazdDuzych).good()) sciezkaGwiazdDuzych = "../../media/Background/Stars-Big_1_1_PC.png";

    if (teksturaGwiazdDuzych.loadFromFile(sciezkaGwiazdDuzych)) {
        teksturaGwiazdDuzych.setRepeated(true);
        gwiazdyDuze.setTexture(teksturaGwiazdDuzych);
        gwiazdyDuze.setColor(sf::Color(255, 255, 255, 210));
    }
    else {
        std::cout << "Blad ladowania tla: " << sciezkaGwiazdDuzych << "\n";
    }
}


void Gra::inicjalizujMenu() {
    tekstTytulu.setFont(czcionka);
    tekstTytulu.setString("NEON ASCEND");
    tekstTytulu.setCharacterSize(50);
    tekstTytulu.setFillColor(sf::Color::Cyan);
    tekstTytulu.setPosition(240.f, 80.f);

    przyciskGraj.setSize(sf::Vector2f(200.f, 50.f));
    przyciskGraj.setFillColor(sf::Color(40, 40, 80));
    przyciskGraj.setPosition(300.f, 220.f);
    tekstGraj.setFont(czcionka);
    tekstGraj.setString("GRAJ");
    tekstGraj.setCharacterSize(24);
    tekstGraj.setFillColor(sf::Color::White);
    tekstGraj.setPosition(370.f, 230.f);

    przyciskWynik.setSize(sf::Vector2f(200.f, 50.f));
    przyciskWynik.setFillColor(sf::Color(40, 40, 80));
    przyciskWynik.setPosition(300.f, 300.f);
    tekstWynik.setFont(czcionka);
    tekstWynik.setString("WYNIKI");
    tekstWynik.setCharacterSize(24);
    tekstWynik.setFillColor(sf::Color::White);
    tekstWynik.setPosition(360.f, 310.f);

    przyciskWyjdz.setSize(sf::Vector2f(200.f, 50.f));
    przyciskWyjdz.setFillColor(sf::Color(80, 40, 40));
    przyciskWyjdz.setPosition(300.f, 380.f);
    tekstWyjdz.setFont(czcionka);
    tekstWyjdz.setString("WYJDZ");
    tekstWyjdz.setCharacterSize(24);
    tekstWyjdz.setFillColor(sf::Color::White);
    tekstWyjdz.setPosition(365.f, 390.f);
}

void Gra::inicjalizujGameOver() {
    tekstGameOver.setFont(czcionka);
    tekstGameOver.setString("GAME OVER");
    tekstGameOver.setCharacterSize(60);
    tekstGameOver.setFillColor(sf::Color::Red);
    tekstGameOver.setPosition(240.f, 100.f);

    tekstWynikuKoncowego.setFont(czcionka);
    tekstWynikuKoncowego.setCharacterSize(30);
    tekstWynikuKoncowego.setFillColor(sf::Color::White);
    tekstWynikuKoncowego.setPosition(260.f, 200.f);

    przyciskRestart.setSize(sf::Vector2f(200.f, 50.f));
    przyciskRestart.setFillColor(sf::Color(40, 80, 40));
    przyciskRestart.setPosition(180.f, 350.f);
    tekstRestart.setFont(czcionka);
    tekstRestart.setString("RESTART");
    tekstRestart.setCharacterSize(24);
    tekstRestart.setFillColor(sf::Color::White);
    tekstRestart.setPosition(230.f, 360.f);

    przyciskQuit.setSize(sf::Vector2f(200.f, 50.f));
    przyciskQuit.setFillColor(sf::Color(80, 40, 40));
    przyciskQuit.setPosition(420.f, 350.f);
    tekstQuit.setFont(czcionka);
    tekstQuit.setString("QUIT");
    tekstQuit.setCharacterSize(24);
    tekstQuit.setFillColor(sf::Color::White);
    tekstQuit.setPosition(490.f, 360.f);
}

void Gra::inicjalizujEkranWynikow() {
    tekstNaglowekWynikow.setFont(czcionka);
    tekstNaglowekWynikow.setString("OSTATNIE WYNIKI");
    tekstNaglowekWynikow.setCharacterSize(40);
    tekstNaglowekWynikow.setFillColor(sf::Color::Cyan);
    tekstNaglowekWynikow.setPosition(220.f, 50.f);

    tekstListaWynikow.setFont(czcionka);
    tekstListaWynikow.setCharacterSize(24);
    tekstListaWynikow.setFillColor(sf::Color::White);
    tekstListaWynikow.setPosition(220.f, 150.f);

    przyciskPowrot.setSize(sf::Vector2f(200.f, 50.f));
    przyciskPowrot.setFillColor(sf::Color(80, 40, 40));
    przyciskPowrot.setPosition(300.f, 500.f);
    tekstPowrot.setFont(czcionka);
    tekstPowrot.setString("POWROT");
    tekstPowrot.setCharacterSize(24);
    tekstPowrot.setFillColor(sf::Color::White);
    tekstPowrot.setPosition(350.f, 510.f);
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

void Gra::zresetujGre() {
    tekstObecnyWynik.setFont(czcionka);
    tekstObecnyWynik.setCharacterSize(24);
    tekstObecnyWynik.setFillColor(sf::Color::White);
    obiektyWGrze.clear();
    obecnyWynik = 0;

    // Resetowanie staminy i kamery
    najwyzszyPunktY = 300.f;
    wynikOstatniegoDoubleJumpa = 0;
    poprzedniaMana = 1;

    kamera.setSize(800.f, 600.f);
    kamera.setCenter(400.f, 300.f);

    obiektyWGrze.push_back(std::make_unique<Gracz>(400.f, 200.f));
    obiektyWGrze.push_back(std::make_unique<Platforma>(0.f, 550.f, 800.f));
    obiektyWGrze.push_back(std::make_unique<Platforma>(350.f, 400.f, 100.f));
    najwyzszaPlatformaY = 400.f;

    generujPlatformy();
}

void Gra::obsluzZdarzenia() {
    sf::Event zdarzenie;
    while (okno.pollEvent(zdarzenie)) {
        if (zdarzenie.type == sf::Event::Closed)
            okno.close();

        if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i pozycjaMyszkiI = sf::Mouse::getPosition(okno);
            sf::Vector2f pozycjaMyszki = okno.mapPixelToCoords(pozycjaMyszkiI);

            if (obecnyStan == StanGry::MENU) {
                if (przyciskGraj.getGlobalBounds().contains(pozycjaMyszki)) {
                    zresetujGre();
                    obecnyStan = StanGry::ROZGRYWKA;
                }
                else if (przyciskWynik.getGlobalBounds().contains(pozycjaMyszki)) {
                    zaladujWynikiZPliku();
                    obecnyStan = StanGry::WYNIKI;
                }
                else if (przyciskWyjdz.getGlobalBounds().contains(pozycjaMyszki)) {
                    okno.close();
                }
            }
            else if (obecnyStan == StanGry::WYNIKI) {
                if (przyciskPowrot.getGlobalBounds().contains(pozycjaMyszki)) {
                    obecnyStan = StanGry::MENU;
                }
            }
            else if (obecnyStan == StanGry::GAME_OVER) {
                if (przyciskRestart.getGlobalBounds().contains(pozycjaMyszki)) {
                    zresetujGre();
                    obecnyStan = StanGry::ROZGRYWKA;
                }
                else if (przyciskQuit.getGlobalBounds().contains(pozycjaMyszki)) {
                    okno.close();
                }
            }
        }
    }
}

void Gra::aktualizuj(float deltaTime) {
    if (obecnyStan == StanGry::ROZGRYWKA) {
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
            // ---------------------------------- Płynna kamera i limit spadania ------------------------------------
            if (gracz->pobierzPozycje().y < najwyzszyPunktY) {
                najwyzszyPunktY = gracz->pobierzPozycje().y;
            }

            float celKameraY = gracz->pobierzPozycje().y;
            if (celKameraY > najwyzszyPunktY + 280.f) celKameraY = najwyzszyPunktY + 280.f;
            if (celKameraY < najwyzszyPunktY) celKameraY = najwyzszyPunktY;

            // Interpolacja płynnego przejścia kamery
            float obecnyKameraY = kamera.getCenter().y;
            kamera.setCenter(400.f, obecnyKameraY + (celKameraY - obecnyKameraY) * 4.f * deltaTime);

            //Zarządzanie staminą
            if (gracz->pobierzMane() == 0 && poprzedniaMana == 1) {
                wynikOstatniegoDoubleJumpa = obecnyWynik;
            }
            poprzedniaMana = gracz->pobierzMane();

            if (gracz->pobierzMane() == 0 && (obecnyWynik - wynikOstatniegoDoubleJumpa >= 10)) {
                gracz->odnawijMane();
            }

            // ---------------------------------------- Koniec Gry po spadku z kadru ---------------------------
            if (gracz->pobierzPozycje().y > najwyzszyPunktY + 280.f + 300.f) {
                zapiszWynik();
                tekstWynikuKoncowego.setString("WYNIK: " + std::to_string(obecnyWynik));

                float camY = kamera.getCenter().y;
                tekstGameOver.setPosition(240.f, camY - 200.f);
                tekstWynikuKoncowego.setPosition(320.f, camY - 100.f);
                przyciskRestart.setPosition(180.f, camY + 50.f);
                tekstRestart.setPosition(230.f, camY + 60.f);
                przyciskQuit.setPosition(420.f, camY + 50.f);
                tekstQuit.setPosition(490.f, camY + 60.f);

                obecnyStan = StanGry::GAME_OVER;
            }

            //Kolizja ----- BONUS
            sf::FloatRect graniceGracza = gracz->pobierzGranice();
            for (auto& obiekt : obiektyWGrze) {
                if (Bonus* bonus = dynamic_cast<Bonus*>(obiekt.get())) {
                    if (!bonus->czyZebrany() && graniceGracza.intersects(bonus->pobierzGranice())) {
                        bonus->zbierz();
                        gracz->superSkok();
                        obecnyWynik += 10;  // Nagroda za bonus od razu ładuje też staminę!
                    }
                }
            }

            //Kolizja -------- PLATFORMA
            if (gracz->pobierzPredkoscY() > 0) {
                for (auto& obiekt : obiektyWGrze) {
                    if (Platforma* platforma = dynamic_cast<Platforma*>(obiekt.get())) {
                        if (platforma->czyAktywna() && graniceGracza.intersects(platforma->pobierzGranice())) {
                            if (graniceGracza.top + graniceGracza.height - 20.f < platforma->pobierzGranice().top) {
                                gracz->rozpoczynijEfektLadowania();
                                gracz->skok();
                                if (!platforma->bylaDotknieta()) {
                                    platforma->oznaczJakoDotknieta();
                                    obecnyWynik++;
                                }
                            }
                        }
                    }
                }
            }
            tekstObecnyWynik.setString("Wynik: " + std::to_string(obecnyWynik));
            tekstObecnyWynik.setPosition(kamera.getCenter().x + 250.f, kamera.getCenter().y - 280.f);
        }

        generujPlatformy();
        usunStarePlatformy();
    }
}

void Gra::rysuj() {
    okno.clear(sf::Color(15, 15, 30));

    if (obecnyStan == StanGry::ROZGRYWKA) {
        okno.setView(kamera);
        rysujTlo();
        for (auto& obiekt : obiektyWGrze) {
            obiekt->rysuj(okno);
        }
        okno.draw(tekstObecnyWynik);

        //UI KOLO STAMINY
        float uiLewo = kamera.getCenter().x - 380.f;
        float uiGora = kamera.getCenter().y - 280.f;

        // Szary podkład
        sf::CircleShape tloKola(16.f);
        tloKola.setFillColor(sf::Color(45, 45, 60));
        tloKola.setPosition(uiLewo, uiGora);
        okno.draw(tloKola);

        float postep = 0.f;
        Gracz* gracz = nullptr;
        for (auto& obiekt : obiektyWGrze) {
            if (auto g = dynamic_cast<Gracz*>(obiekt.get())) {
                gracz = g;
                break;
            }
        }

        if (gracz) {
            if (gracz->pobierzMane() > 0) {
                postep = 1.f;
            } else {
                postep = static_cast<float>(obecnyWynik - wynikOstatniegoDoubleJumpa) / 10.f;
                if (postep > 1.f) postep = 1.f;
                if (postep < 0.f) postep = 0.f;
            }
        }

        // TriangleFan do paska postępu
        sf::VertexArray koloLadowania(sf::TriangleFan);
        sf::Vector2f srodek(uiLewo + 16.f, uiGora + 16.f);
        sf::Color kolorWskaznika = (postep >= 1.f) ? sf::Color::Green : sf::Color::Cyan;

        koloLadowania.append(sf::Vertex(srodek, kolorWskaznika));
        int iloscPunktowKola = 30;
        for (int i = 0; i <= iloscPunktowKola * postep; ++i) {
            float kat = (i * 360.f / iloscPunktowKola) - 90.f;
            float rad = kat * 3.14159265f / 180.f;
            koloLadowania.append(sf::Vertex(sf::Vector2f(srodek.x + std::cos(rad) * 16.f, srodek.y + std::sin(rad) * 16.f), kolorWskaznika));
        }

        if (postep > 0.f) {
            okno.draw(koloLadowania);
        }
    }
    else if (obecnyStan == StanGry::MENU) {
        okno.setView(okno.getDefaultView());
        okno.draw(tekstTytulu);
        okno.draw(przyciskGraj);
        okno.draw(tekstGraj);
        okno.draw(przyciskWynik);
        okno.draw(tekstWynik);
        okno.draw(przyciskWyjdz);
        okno.draw(tekstWyjdz);
    }
    else if (obecnyStan == StanGry::GAME_OVER) {
        okno.setView(kamera);
        rysujTlo();
        for (auto& obiekt : obiektyWGrze) {
            obiekt->rysuj(okno);
        }
        okno.draw(tekstObecnyWynik);
        okno.draw(tekstGameOver);
        okno.draw(tekstWynikuKoncowego);
        okno.draw(przyciskRestart);
        okno.draw(tekstRestart);
        okno.draw(przyciskQuit);
        okno.draw(tekstQuit);
    }
    else if (obecnyStan == StanGry::WYNIKI) {
        okno.setView(okno.getDefaultView());
        okno.draw(tekstNaglowekWynikow);
        okno.draw(tekstListaWynikow);
        okno.draw(przyciskPowrot);
        okno.draw(tekstPowrot);
    }

    okno.display();
}

void Gra::rysujTlo() {
    sf::Vector2f rozmiarWidoku = kamera.getSize();
    float lewyBrzeg = kamera.getCenter().x - rozmiarWidoku.x / 2.f;
    float gornyBrzeg = kamera.getCenter().y - rozmiarWidoku.y / 2.f;

    if (teksturaTla.getSize().y > 0) {
        int przesuniecie = static_cast<int>(-kamera.getCenter().y * 0.12f) % static_cast<int>(teksturaTla.getSize().y);
        if (przesuniecie < 0) przesuniecie += static_cast<int>(teksturaTla.getSize().y);
        tlo.setPosition(lewyBrzeg, gornyBrzeg);
        tlo.setTextureRect(sf::IntRect(0, przesuniecie, static_cast<int>(rozmiarWidoku.x), static_cast<int>(rozmiarWidoku.y)));
        okno.draw(tlo);
    }

    if (teksturaGwiazdMalych.getSize().y > 0) {
        int przesuniecie = static_cast<int>(kamera.getCenter().y * 0.35f) % static_cast<int>(teksturaGwiazdMalych.getSize().y);
        if (przesuniecie < 0) przesuniecie += static_cast<int>(teksturaGwiazdMalych.getSize().y);
        gwiazdyMale.setPosition(lewyBrzeg, gornyBrzeg);
        gwiazdyMale.setTextureRect(sf::IntRect(0, przesuniecie, static_cast<int>(rozmiarWidoku.x), static_cast<int>(rozmiarWidoku.y)));
        okno.draw(gwiazdyMale);
    }

    if (teksturaGwiazdDuzych.getSize().y > 0) {
        int przesuniecie = static_cast<int>(kamera.getCenter().y * 0.55f) % static_cast<int>(teksturaGwiazdDuzych.getSize().y);
        if (przesuniecie < 0) przesuniecie += static_cast<int>(teksturaGwiazdDuzych.getSize().y);
        gwiazdyDuze.setPosition(lewyBrzeg, gornyBrzeg);
        gwiazdyDuze.setTextureRect(sf::IntRect(0, przesuniecie, static_cast<int>(rozmiarWidoku.x), static_cast<int>(rozmiarWidoku.y)));
        okno.draw(gwiazdyDuze);
    }
}
void Gra::generujPlatformy() {
    while (najwyzszaPlatformaY > kamera.getCenter().y - 600.f) {
        najwyzszaPlatformaY -= 140.f;
        float losowyX = rozkladX(generatorRNG);

        TypPlatformy wylosowanyTyp = TypPlatformy::ZWYKLA;

        std::uniform_int_distribution<int> losujSzansę(1, 100);
        int szansa = losujSzansę(generatorRNG);

        if(obecnyWynik >= 25)
        {
            if (szansa <= 30) wylosowanyTyp = TypPlatformy::MIGAJACA;
            else if (szansa <= 60) wylosowanyTyp = TypPlatformy::KRUCHA;
        }
        else if(obecnyWynik >= 15)
        {
            if (szansa <= 40) wylosowanyTyp = TypPlatformy::KRUCHA;
        }


        obiektyWGrze.push_back(std::make_unique<Platforma>(losowyX, najwyzszaPlatformaY, 120.f, wylosowanyTyp));

        if (obecnyWynik >= 5) {
            std::uniform_int_distribution<int> losujBonus(1, 100);
            if (losujBonus(generatorRNG) <= 10) {
                obiektyWGrze.push_back(std::make_unique<Bonus>(losowyX + 45.f, najwyzszaPlatformaY - 40.f));
            }
        }
    }


}

void Gra::usunStarePlatformy() {
    float dolEkranu = kamera.getCenter().y + 400.f;
    obiektyWGrze.erase(std::remove_if(obiektyWGrze.begin(), obiektyWGrze.end(),
                                      [dolEkranu](const std::unique_ptr<Obiekt>& obj) {
                                          if (dynamic_cast<Platforma*>(obj.get())) {
                                              return obj->pobierzPozycje().y > dolEkranu;
                                          }
                                          if (Bonus* b = dynamic_cast<Bonus*>(obj.get())) {
                                              // Usuwamy bonus jeśli wypadł z ekranu LUB jeśli gracz go zebrał
                                              return b->pobierzPozycje().y > dolEkranu || b->czyZebrany();
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

void Gra::zaladujWynikiZPliku() {
    std::ifstream plik("wyniki.txt");
    std::string linia;
    std::vector<std::string> wszystkieWyniki;

    if (plik.is_open()) {
        while (std::getline(plik, linia)) {
            wszystkieWyniki.push_back(linia);
        }
        plik.close();
    }

    std::string tekstDoWyswietlenia = "";
    int iloscWynikow = wszystkieWyniki.size();

    if (iloscWynikow == 0) {
        tekstDoWyswietlenia = "Brak rozegranych gier!";
    } else {
        int start = std::max(0, iloscWynikow - 5);
        for (int i = start; i < iloscWynikow; i++) {
            tekstDoWyswietlenia += wszystkieWyniki[i] + "\n\n";
        }
    }

    tekstListaWynikow.setString(tekstDoWyswietlenia);
}
