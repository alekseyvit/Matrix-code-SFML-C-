#pragma once

#include "Letter.h"

#include <vector>
#include <SFML/Graphics.hpp>

class Matrix
{
    std::vector<std::vector<Letter>> _matrix;
    int _maxAlpha = 255;
    int _alphaInitThreshold = 230;
    int _alphaRedThreshold = 240;
    int _alphaStep = 25; // насколько уменьшается яркость
public:
    Matrix(int X, int Y);

    // Initialization of start Letters
    void initialization();
    
    void drawMatrix(sf::RenderWindow& window) const;
    void moveMatrixOfLetters();

    void createNewLayer();

    void makeAlphaRain();
};

