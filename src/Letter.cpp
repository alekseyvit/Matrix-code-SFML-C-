#include "Letter.h"

sf::Font createFont()
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        exit(-1);
    }
    return font;
}
sf::Font Letter::_font(createFont());

Letter::Letter() {
    _text.setFont(_font);
    _text.setCharacterSize(_size);//TEMP
    _text.setFillColor(sf::Color(0, 255, 0, _alpha));
    _text.setString(_letter);
    _text.setPosition(0, 0);
    _text.move(_posX, _posY);
}

void Letter::moveDown() {
    _text.move(0, _size_y);
}

int Letter::getSizeX() {
    return _size_x;
}

int Letter::getSizeY() {
    return _size_y;
}

int& Letter::alpha() {
    return _alpha;
}

sf::Text& Letter::text() {
    return _text;
}

int& Letter::posX() {
    return _posX;
}

int& Letter::posY() {
    return _posY;
}

void Letter::updateText() {
    //_text.setCharacterSize(_size);
    sf::Color tmp = _text.getFillColor();
    tmp.a = _alpha;
    _text.setFillColor(tmp);
    _text.setOutlineColor(sf::Color(0, 0, 0, 0));//TEMP
    _text.setString(_letter);
    _text.setPosition(0, 0);
    _text.move(_posX, _posY);
}

void Letter::drawFallingLetter(sf::RenderWindow& window) const {
    window.draw(_text);
}

//inline void Letter::moveFallingLetter(sf::RenderWindow& window, float sec) {
//    float half_window_y = window.getSize().y / 2;
//    float delta_time = (sec - this->time);
//    this->time = sec;
//
//    float curr_y = y_0;
//    if ((GRAVITY * sec) * delta_time < MAX_DELTA_Y) {
//        //curr_y += GRAVITY * sec * sec / 2.0f;
//
//        curr_y += (GRAVITY * sec) * delta_time;
//        cout << (GRAVITY * sec) * delta_time << endl;
//    }
//    else {
//        curr_y += MAX_DELTA_Y;
//        cout << (GRAVITY * sec) * delta_time << endl;
//    }
//    y_0 = curr_y;
//
//    while (curr_y > half_window_y) {
//        curr_y -= half_window_y;
//        this->setLetter(' ' + rand() % ALPHABET_CAPACITY);
//        sf::Vector2f offset(rand() % window.getSize().x, 0);
//        this->setPosition(offset);
//        this->setSize(20 + rand() % 40);
//    }
//
//    Uint8 curr_alpha = 255 * (half_window_y - curr_y) / half_window_y;
//    _text.setFillColor(sf::Color(0, 255, 0, curr_alpha));
//    _text.setPosition(sf::Vector2f(_text.getPosition().x, curr_y));
//    window.draw(_text);
//}

