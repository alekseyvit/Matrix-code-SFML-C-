#pragma once

#include "Letter.h"

#include <vector>
#include <SFML/Graphics.hpp>

class Matrix
{
    std::vector<std::vector<Letter>> _matrix;

public:
    Matrix(int X, int Y);

    // Initialization of start Letters
    //for (size_t x = 0; x < matrix.size(); x++) {
    //    for (size_t y = 0; y < matrix[0].size(); y++) {
    //        // init alpha chanell
    //        if (matrix[x][y]._alpha >= 230) {
    //            
    //            int max_alpha = 255;
    //            for (int _y = y; _y >= 0; _y--) {
    //                matrix[x][_y]._alpha = max_alpha;
    //                matrix[x][_y]._text.setFillColor(sf::Color(255, 0, 0, max_alpha));
    //                //cout << x << ", " << _y << endl;
    //                if (max_alpha - 25 >= 0)
    //                    max_alpha -= 25;
    //                else
    //                    max_alpha = 0;
    //            }
    //        }
    //        
    //        // init position of each letter
    //        matrix[x][y]._pos_x = x * matrix[x][y]._size_x;
    //        matrix[x][y]._pos_y = y * matrix[x][y]._size_y;

    //        // init letter
    //        // matrix[x][y]._letter = 'a' + rand() % ALPHABET_CAPACITY;

    //        matrix[x][y].update_text();
    //    }
    //}

    void drawMatrix(sf::RenderWindow& window) const;
    void moveMatrixOfLetters();

    //void createNewLayer(std::vector<vector<Letter>>& matrix) {
    //    //cout << "createNewLaeyer" << endl;
    //    for (size_t x = 0; x < matrix.size(); x++) {
    //        int y = 0;
    //        matrix[x][y] = Letter();
    //        // init position of each letter
    //        matrix[x][y]._pos_x = x * matrix[x][y]._size_x;
    //        matrix[x][y]._pos_y = y * matrix[x][y]._size_y;
    //
    //        matrix[x][y].update_text();
    //        if (matrix[x][0]._alpha >= 240) {
    //            matrix[x][0]._alpha = 255;
    //            matrix[x][0]._text.setFillColor(sf::Color(255, 0, 0, matrix[x][0]._alpha));//RED
    //        }
    //    }
    //}



    //void makeAlphaRain(std::vector<vector<Letter>>& matrix) {
    //    //cout << "makeAlphaRain" << endl;
    //    for (size_t x = 0; x < matrix.size(); x++) {
    //        for (int y = matrix[0].size() - 1; y >= 0; y--) {
    //            // init alpha chanell
    //            if (matrix[x][y]._alpha == 255 && (int)(matrix[x][y]._text.getFillColor().r) == 255) {
    //
    //                int max_alpha = 255;
    //                for (int _y = y; _y >= 0; _y--) {
    //                    matrix[x][_y]._alpha = max_alpha;
    //                    matrix[x][_y]._text.setFillColor(sf::Color(255, 0, 0, max_alpha));//RED
    //                    //cout << x << ", " << _y << endl;
    //                    if (max_alpha - 255 / RAIN_LENGTH >= 0)
    //                        max_alpha -= 255 / RAIN_LENGTH;
    //                    else {
    //                        max_alpha = 0;
    //                        break;
    //                    }     
    //                }
    //            }
    //        }
    //    }
    //}
};

