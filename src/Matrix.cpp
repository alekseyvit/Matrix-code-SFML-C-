#include "Matrix.h"
//#include "Letter.h"

Matrix::Matrix(int X, int Y) {
    _matrix.resize(Y);
    for (auto it = _matrix.begin(); it < _matrix.end(); ++it) {
        it->resize(X);
    }
}


// Initialization of start Letters

void Matrix::initialization() {
    for (size_t y = 0; y < _matrix.size(); y++) {
        for (size_t x = 0; x < _matrix[0].size(); x++) {
            // init alpha chanell
            if (_matrix[y][x].alpha() >= _alphaThreshold) {
                for (int _y = x; _y >= 0; _y--) {
                    _matrix[_y][x].alpha() = _maxAlpha;
                    _matrix[_y][x].text().setFillColor(sf::Color(255, 0, 0, _maxAlpha));
                    if (_maxAlpha - _alphaStep >= 0)
                        _maxAlpha -= _alphaStep;
                    else
                        _maxAlpha = 0;
                }
            }

            // init position of each letter
            _matrix[y][x].posX() = x * _matrix[y][x].getSizeX();
            _matrix[y][x].posY() = y * _matrix[y][x].getSizeY();

            // init letter
            // matrix[x][y]._letter = 'a' + rand() % ALPHABET_CAPACITY;

            _matrix[y][x].update_text();
        }
    }
}

void Matrix::drawMatrix(sf::RenderWindow& window) const {
    for (auto& line : _matrix) {
        for (auto& el : line) {
            el.drawFallingLetter(window);
        }
    }
}

void Matrix::moveMatrixOfLetters() {
    // TODO make optimization here by moving the whole line? 
    for (size_t y = _matrix.size() - 1; y >= 1; y--) {
        for (size_t x = 0; x < _matrix[0].size(); x++) {
            _matrix[y][x] = Letter(std::move(_matrix[y - 1][x]));
        }
    }
}
