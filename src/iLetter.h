#pragma once

#include <SFML/Graphics.hpp>

class iLetter {
public:
    virtual int getSizeX() const = 0;
    virtual int getSizeY() const = 0;
    virtual int& alpha() = 0;
    virtual sf::Text& text() = 0;
    virtual int& posX() = 0;
    virtual int& posY() = 0;

    virtual void moveDown() = 0;

    virtual void updateText() = 0;
    virtual void drawFallingLetter(sf::RenderWindow& window) const = 0;
    
    virtual ~iLetter() {}
};
