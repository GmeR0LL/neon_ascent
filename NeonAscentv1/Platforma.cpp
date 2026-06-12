#include "Platforma.h"


//platforma dodalem boola
Platforma::Platforma(float x, float y, float szerokosc, TypPlatformy typPlatformy) : Obiekt(x, y), czyDotknieta(false), typ(typPlatformy), zegarMigotania(0.f), widoczna(true), zniszczona(false) {
    ksztalt.setSize(sf::Vector2f(szerokosc, 20.f));
    // Kolory platform
    if(typ == TypPlatformy::ZWYKLA)
    {
        ksztalt.setFillColor(sf::Color(255,0,255)); // Różowa
    }
    else if(typ == TypPlatformy::KRUCHA)
    {
        ksztalt.setFillColor(sf::Color(255, 100, 0)); //Pomaranczowa(zanika)
    }
    else if (typ == TypPlatformy::MIGAJACA)
    {
        ksztalt.setFillColor(sf::Color(0, 255, 255)); // Błękitna (miga)
    }

    ksztalt.setPosition(pozycja);
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
        okno.draw(ksztalt);
    }
}

sf::FloatRect Platforma::pobierzGranice() const {
    return ksztalt.getGlobalBounds();
}


//dotknieta platforma
void Platforma::oznaczJakoDotknieta() {
    czyDotknieta = true;

    if (typ == TypPlatformy::KRUCHA) {
        zniszczona = true;
    }
    else if (typ == TypPlatformy::ZWYKLA) {
        ksztalt.setFillColor(sf::Color(100, 0, 100)); // Zwykła tylko ciemnieje
    }
    ksztalt.setFillColor(sf::Color(100, 0, 100)); //ciemny roz
 }