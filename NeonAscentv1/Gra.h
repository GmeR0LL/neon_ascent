#ifndef GRA_H
#define GRA_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random>
#include <fstream>
#include "Obiekt.h"

enum class StanGry { MENU, ROZGRYWKA, GAME_OVER, WYNIKI};

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
    StanGry obecnyStan;

    float najwyzszyPunktY; //sledzenie punktu
    int wynikOstatniegoDoubleJumpa;
    int poprzedniaMana;


    //czcionka z zasobow aby dzialala
    sf::Font czcionka;

    //dynamiczne tlo
    sf::Texture teksturaTla;
    sf::Texture teksturaGwiazdMalych;
    sf::Texture teksturaGwiazdDuzych;
    sf::Sprite tlo;
    sf::Sprite gwiazdyMale;
    sf::Sprite gwiazdyDuze;


    //menu glowne
    sf::Text tekstTytulu;
    sf::RectangleShape przyciskGraj;
    sf::Text tekstGraj;
    sf::RectangleShape przyciskWynik;
    sf::Text tekstWynik;
    sf::RectangleShape przyciskWyjdz;
    sf::Text tekstWyjdz;


    //menu przegranej
    sf::Text tekstGameOver;
    sf::Text tekstWynikuKoncowego;
    sf::RectangleShape przyciskRestart;
    sf::Text tekstRestart;
    sf::RectangleShape przyciskQuit;
    sf::Text tekstQuit;

    //ekran wynikow
    sf::Text tekstNaglowekWynikow;
    sf::Text tekstListaWynikow;
    sf::RectangleShape przyciskPowrot;
    sf::Text tekstPowrot;


    //funkcje pomocniczne
    void obsluzZdarzenia();
    void aktualizuj(float deltaTime);
    void rysuj();

    //potrzebne funkcje
    void generujPlatformy();
    void usunStarePlatformy();
    void zapiszWynik();
    void inicjalizujEkranWynikow();
    void zaladujWynikiZPliku();


    //organizacja menu
    void inicjalizujMenu();
    void inicjalizujGameOver();
    void inicjalizujTlo();
    void rysujTlo();
    void zresetujGre();

     sf::Text tekstObecnyWynik; //Licznik w rogu

public:
    Gra();
    void uruchom();
};

#endif // GRA_H
