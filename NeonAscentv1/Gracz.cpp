#include "Gracz.h"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

Gracz::Gracz(float x, float y) : Obiekt(x, y), obecnaKlatka(0), czasAnimacji(0.f), czasKlatki(0.16f), animacjaSkokuAktywna(true), patrzyWLewo(false), efektLadowaniaAktywny(false), czasEfektuLadowania(0.f), poprzedniPrzyciskSkoku(false), mana(1) {
    ksztalt.setSize(sf::Vector2f(30.f, 30.f));
    ksztalt.setFillColor(sf::Color::Cyan);
    ksztalt.setPosition(pozycja);

    teksturyAnimacji.reserve(6);
    prostokatyAnimacji.reserve(6);

    const std::vector<std::string> klatki = {
        "a6.png",
        "a1.png",
        "a2.png",
        "a3.png",
        "a4.png",
        "a5.png"
    };

    for (const auto& nazwaPliku : klatki) {
        std::string sciezka = "media/bohater/" + nazwaPliku;
        if (!std::ifstream(sciezka).good()) sciezka = "../../media/bohater/" + nazwaPliku;

        sf::Image obraz;
        if (obraz.loadFromFile(sciezka)) {
            teksturyAnimacji.emplace_back();
            teksturyAnimacji.back().loadFromImage(obraz);
            prostokatyAnimacji.push_back(sf::IntRect(0, 0, obraz.getSize().x, obraz.getSize().y));
        }
        else {
            std::cout << "Blad ladowania gracza: " << sciezka << "\n";
        }
    }

    if (!teksturyAnimacji.empty()) {
        slime.setTexture(teksturyAnimacji[0]);
        slime.setTextureRect(prostokatyAnimacji[0]);
        slime.setScale(5.f, 5.f);
    }

    szybkoscRuchu = 400.f;
    grawitacja = 1200.f; //w dol
    silaSkoku = -750.f;   // do gory
}

void Gracz::aktualizuj(float deltaTime) {
    // wektor przyspieszenia
    predkosc.y += grawitacja * deltaTime;

    //Sterowanie
    predkosc.x = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        predkosc.x = -szybkoscRuchu;
        patrzyWLewo = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        predkosc.x = szybkoscRuchu;
        patrzyWLewo = false;
    }

    bool przyciskSkoku = sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    if (przyciskSkoku && !poprzedniPrzyciskSkoku && mana > 0) {
        mana--;
        predkosc.y = silaSkoku * 1.15f;
        rozpoczynijAnimacjeSkoku();
    }
    poprzedniPrzyciskSkoku = przyciskSkoku;

    if (!teksturyAnimacji.empty()) {
        czasAnimacji += deltaTime;
        while (czasAnimacji >= czasKlatki) {
            czasAnimacji -= czasKlatki;
            obecnaKlatka = (obecnaKlatka + 1) % static_cast<int>(teksturyAnimacji.size());
        }
        slime.setTexture(teksturyAnimacji[obecnaKlatka]);
        slime.setTextureRect(prostokatyAnimacji[obecnaKlatka]);
    }

    //Aktualizacja pozycji o wektor predkosci
    pozycja += predkosc * deltaTime;

    if (efektLadowaniaAktywny) {
        czasEfektuLadowania += deltaTime;
        if (czasEfektuLadowania >= 0.09f) {
            efektLadowaniaAktywny = false;
            czasEfektuLadowania = 0.f;
        }
    }

    // Zawijanie ekranu
    if (pozycja.x < 0) pozycja.x = 800.f;
    if (pozycja.x > 800) pozycja.x = 0.f;

    ksztalt.setPosition(pozycja);

    if (!teksturyAnimacji.empty()) {
        sf::Vector2f skala(3.f, 3.f);

        if (efektLadowaniaAktywny) {
            skala.x *= 1.30f;
            skala.y *= 0.68f;
        }
        else if (std::abs(predkosc.y) < 50.f) {
            skala.x *= 1.18f;
            skala.y *= 0.78f;
        }
        else if (predkosc.y < 0.f) {
            skala.x *= 0.82f;
            skala.y *= 1.22f;
        }
        else if (predkosc.y > 0.f) {
            skala.x *= 0.92f;
            skala.y *= 1.10f;
        }

        const sf::IntRect& klatka = prostokatyAnimacji[obecnaKlatka];
        slime.setOrigin(klatka.width / 2.f, klatka.height / 2.f);
        slime.setPosition(pozycja.x + 15.f, pozycja.y + 15.f);
        slime.setScale(patrzyWLewo ? skala.x : -skala.x, skala.y);
    }
}

void Gracz::skok() {
    predkosc.y = silaSkoku;
}

void Gracz::rysuj(sf::RenderWindow& okno) {
    if (!teksturyAnimacji.empty()) {
        okno.draw(slime);
    }
    else {
        okno.draw(ksztalt);
    }
}

sf::FloatRect Gracz::pobierzGranice() const {
    return ksztalt.getGlobalBounds();
}

void Gracz::superSkok() {
    predkosc.y = -2200.f; // Wystrzeliwuje gracza wysoko w gore
    rozpoczynijAnimacjeSkoku();
}

void Gracz::rozpoczynijAnimacjeSkoku() {
    if (teksturyAnimacji.empty()) {
        return;
    }

    animacjaSkokuAktywna = true;
    czasAnimacji = 0.f;
    obecnaKlatka = 0;
    slime.setTexture(teksturyAnimacji[0]);
    slime.setTextureRect(prostokatyAnimacji[0]);
}

void Gracz::rozpoczynijEfektLadowania() {
    efektLadowaniaAktywny = true;
    czasEfektuLadowania = 0.f;
}

void Gracz::odnawijMane() {
    mana = 1;
}
