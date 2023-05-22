#pragma once

#include <chrono>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

//const float GRAVITY = 9.8f;
//const float MAX_DELTA_Y = 2.150f;
const size_t ALPHABET_CAPACITY = 25;
const int MAX_LIFE_TIME_SEC = 30;
const int RAIN_LENGTH = 10;

class Letter {
public:
    static sf::Font _font;
private:
    char _letter = 'a' + rand() % ALPHABET_CAPACITY;;
    int _size = 15;// 15;
    int _size_x = 12;//12;// 25;
    int _size_y = 12;//12;// 25;
    int _alpha = rand() % 255;
    //int _live_time = rand() % MAX_LIFE_TIME_SEC;

    int _pos_x = 0;
    int _pos_y = 0;

    sf::Text _text;
public:
    Letter();
    Letter(const Letter& other) = default;
    Letter(Letter&& other) noexcept = default;

    Letter& operator=(const Letter& other) = default;
    Letter& operator=(Letter&& other) noexcept = default;

    int getSizeX();
    int getSizeY();
    int& alpha();
    sf::Text& text();
    int& posX();
    int& posY();

    void moveDown();

    void updateText();
    void drawFallingLetter(sf::RenderWindow& window) const;
    //void moveFallingLetter(sf::RenderWindow& window, float sec);
};
