#include "Platforma.h"
#include <fstream>
#include <iostream>


//static
sf::Texture Platforma::teksturaZwykla;
sf::Texture Platforma::teksturaKrucha;
sf::Texture Platforma::teksturaMigajaca;
bool Platforma::zaladowanoTekstury = false;

//platforma dodalem boola
Platforma::Platforma(float x, float y, float szerokosc, TypPlatformy typPlatformy) : Obiekt(x, y), czyDotknieta(false), typ(typPlatformy), zegarMigotania(0.f), widoczna(true), zniszczona(false) {
    if (!zaladowanoTekstury) {
        std::string s1 = "media/platforma/plat1.png";
        if (!std::ifstream(s1).good()) s1 = "../../" + s1;
        if (!teksturaZwykla.loadFromFile(s1)) std::cout << "Blad: " << s1 << "\n";

        std::string s2 = "media/platforma/plat2.png";
        if (!std::ifstream(s2).good()) s2 = "../../" + s2;
        if (!teksturaMigajaca.loadFromFile(s2)) std::cout << "Blad: " << s2 << "\n";

        std::string s3 = "media/platforma/plat3.png";
        if (!std::ifstream(s3).good()) s3 = "../../" + s3;
        if (!teksturaKrucha.loadFromFile(s3)) std::cout << "Blad: " << s3 << "\n";

        zaladowanoTekstury = true;
    }

    // Kolory platform
    if(typ == TypPlatformy::ZWYKLA)
    {
        sprite.setTexture(teksturaZwykla); // Różowa
    }
    else if(typ == TypPlatformy::KRUCHA)
    {
        sprite.setTexture(teksturaKrucha); //Pomaranczowa(zanika)
    }
    else if (typ == TypPlatformy::MIGAJACA)
    {
        sprite.setTexture(teksturaMigajaca); // Błękitna (miga)
    }

    float teksturaSzer = static_cast<float>(sprite.getTexture()->getSize().x);
    if (teksturaSzer > 0) {
        float skalaX = szerokosc / teksturaSzer;
        sprite.setScale(skalaX, 1.0f);
    }

    sprite.setPosition(pozycja);
}

void Platforma::aktualizuj(float deltaTime) {
    if (typ == TypPlatformy::MIGAJACA && !zniszczona) {
        //Odmierza czas dla platform migajacych
        zegarMigotania += deltaTime;
        if (zegarMigotania >= 2.0f) { // Co 2 sekundy
            widoczna = !widoczna;     // zmiana widocznosci
            zegarMigotania = 0.f;
        }
    }
}

void Platforma::rysuj(sf::RenderWindow& okno) {
    //Rysujemy, gdy jest widoczna i nie jest zniszczona
    if (widoczna && !zniszczona) {
        okno.draw(sprite);
    }
}

sf::FloatRect Platforma::pobierzGranice() const {
    return sprite.getGlobalBounds();
}

//dotknieta platforma
void Platforma::oznaczJakoDotknieta() {
    czyDotknieta = true;

    if (typ == TypPlatformy::KRUCHA) {
        zniszczona = true;
    }
    else if (typ == TypPlatformy::ZWYKLA) {
        sprite.setColor(sf::Color(100, 100, 100)); // Zwykła tylko ciemnieje
    }
}

bool Platforma::czyAktywna() const {
    return widoczna && !zniszczona;
}