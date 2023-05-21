#include "Matrix.h"
//#include "Letter.h"

Matrix::Matrix(int X, int Y) {
    _matrix.resize(Y);
    for (auto it = _matrix.begin(); it < _matrix.end(); ++it) {
        it->resize(X);
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
