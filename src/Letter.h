#pragma once

#include "iLetter.h"

#include <chrono>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

//const float GRAVITY = 9.8f;
//const float MAX_DELTA_Y = 2.150f;
const size_t ALPHABET_CAPACITY = 26;
const int MAX_LIFE_TIME_SEC = 30;

class Letter : public iLetter {
public:
    static sf::Font _font;
private:
    char _letter = 'a' + rand() % ALPHABET_CAPACITY;;
    int _size = 15;// 15;
    int _sizeX = 12;//12;// 25;
    int _sizeY = 12;//12;// 25;
    int _alpha = rand() % 255;
    //int _live_time = rand() % MAX_LIFE_TIME_SEC;

    int _posX = 0;
    int _posY = 0;

    sf::Text _text;
public:
    Letter();

    int getSizeX() const;
    int getSizeY() const;
    int& alpha();
    sf::Text& text();
    int& posX();
    int& posY();

    void moveDown();

    void updateText();
    void drawFallingLetter(sf::RenderWindow& window) const;
};
