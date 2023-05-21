#include "Matrix.h"
//#include "Letter.h"

Matrix::Matrix(int X, int Y) {
    _matrix.resize(Y);
    for (auto it = _matrix.begin(); it < _matrix.end(); ++it) {
        it->resize(X);
    }
}

void Matrix::initialization() {
    for (size_t y = 0; y < _matrix.size(); ++y) {
        for (size_t x = 0; x < _matrix[0].size(); ++x) {
            // init alpha chanell
            if (_matrix[y][x].alpha() >= _alphaInitThreshold) {
                for (int _y = y; _y >= 0; --_y) {
                    int currAlpha = 255;
                    _matrix[_y][x].alpha() = currAlpha;
                    _matrix[_y][x].text().setFillColor(sf::Color(255, 0, 0, currAlpha));
                    if (currAlpha - _alphaStep >= 0)
                        currAlpha -= _alphaStep;
                    else
                        currAlpha = 0;
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
    for (size_t y = _matrix.size() - 1; y >= 1; --y) {
        for (size_t x = 0; x < _matrix[0].size(); ++x) {
            _matrix[y][x] = std::move(_matrix[y - 1][x]);
        }
    }
}

void Matrix::createNewLayer() {
    //cout << "createNewLayer" << endl;
    for (size_t x = 0; x < _matrix[0].size(); ++x) {
        int y = 0;
        _matrix[y][x] = Letter();
        // init position of each letter
        _matrix[y][x].posX() = x * _matrix[y][x].getSizeX();
        _matrix[y][x].posY() = y * _matrix[y][x].getSizeY();

        _matrix[y][x].update_text();
        if (_matrix[y][0].alpha() >= _alphaThreshold) {
            _matrix[y][0].alpha() = _maxAlpha;
            _matrix[y][0].text().setFillColor(sf::Color(_maxAlpha, 0, 0, _matrix[y][0].alpha()));//RED
        }
    }
}

void Matrix::makeAlphaRain() {
    //cout << "makeAlphaRain" << endl;
    for (size_t y = 0; y < _matrix.size(); ++y) {
        for (int x = _matrix[0].size() - 1; x >= 0; --x) {
            // init alpha chanell
            if (_matrix[y][x].alpha() == _maxAlpha &&
                static_cast<int>(_matrix[y][x].text().getFillColor().r) == _maxAlpha) {

                int max_alpha = 255;
                for (int _x = x; _x >= 0; --_x) {
                    _matrix[y][_x].alpha() = max_alpha;
                    _matrix[y][_x].text().setFillColor(sf::Color(_maxAlpha, 0, 0, max_alpha));//RED
                                                                                              //cout << x << ", " << _y << endl;
                    if (max_alpha - _maxAlpha / RAIN_LENGTH >= 0)
                        max_alpha -= _maxAlpha / RAIN_LENGTH;
                    else {
                        //max_alpha = 0;
                        break;
                    }
                }
            }
        }
    }
}
