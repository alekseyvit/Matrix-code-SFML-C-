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
    _text.move(0, _sizeY);
}

int Letter::getSizeX() const {
    return _sizeX;
}

int Letter::getSizeY() const {
    return _sizeY;
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
