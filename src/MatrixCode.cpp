#include "Letter.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


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

//void moveMatrixOfLetters(std::vector<vector<Letter>>& matrix) {
//    // TODO make optimization here by moving the whole line? 
//    for (size_t x = 0; x < matrix.size(); x++) {
//        for (size_t y = matrix[0].size() - 1; y > 0; y--) {
//            matrix[x][y] = Letter(matrix[x][y - 1]);
//        }
//        //matrix[x][0] = Letter();
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

void drawMatrix(vector<vector<Letter>>& matrix, sf::RenderWindow& window) {
    //for (auto line = matrix.begin(); line < matrix.end(); line++) {
    //    for (auto it = line->begin(); it < line->end(); it++) {
    //        it->drawFallingLetter(window);
    //    }
    //}
    for (auto& line : matrix) {
        for (auto& el : line) {
            el.drawFallingLetter(window);
        }
    }
}

int main()
{
    //sf::RenderWindow window(sf::VideoMode(1366 / 2, 768 / 2), "Falling Red Lines");
    sf::RenderWindow window(sf::VideoMode(1366, 768), "Falling Red Lines", sf::Style::Fullscreen);

    Clock clock;
    clock.restart();

    srand(time(0));

    Letter one_letter;
    int numLettersX = 0;
    if (window.getSize().x % one_letter.getSizeX() == 0.0)
        numLettersX = window.getSize().x / one_letter.getSizeX();
    else
        numLettersX = window.getSize().x / one_letter.getSizeX() + 1;
    
    vector<vector<Letter>> matrix(numLettersX);
    for (auto it = matrix.begin(); it < matrix.end(); ++it) {
        it->resize(window.getSize().y / one_letter.getSizeY());
    }

    // Initialization of start Letters
    /*for (size_t x = 0; x < matrix.size(); x++) {
        for (size_t y = 0; y < matrix[0].size(); y++) {
            // init alpha chanell
            if (matrix[x][y]._alpha >= 230) {
                
                int max_alpha = 255;
                for (int _y = y; _y >= 0; _y--) {
                    matrix[x][_y]._alpha = max_alpha;
                    matrix[x][_y]._text.setFillColor(sf::Color(255, 0, 0, max_alpha));
                    //cout << x << ", " << _y << endl;
                    if (max_alpha - 25 >= 0)
                        max_alpha -= 25;
                    else
                        max_alpha = 0;
                }
            }
            
            // init position of each letter
            matrix[x][y]._pos_x = x * matrix[x][y]._size_x;
            matrix[x][y]._pos_y = y * matrix[x][y]._size_y;

            // init letter
            // matrix[x][y]._letter = 'a' + rand() % ALPHABET_CAPACITY;

            matrix[x][y].update_text();
        }
    }

    // init one collumn
    int collumn_number = matrix.size() - 1;
    for (int y = 0; y < matrix[0].size(); y++) {
        matrix[collumn_number][y]._alpha = 255;
        matrix[collumn_number][y]._letter = 'a' + y;
        matrix[collumn_number][y].update_text();
    }
    
    // text that must be shown all the time
    // Text:
    //esc - exit\n
    //p - pause
    Text esc_text;
    esc_text.setFont(Letter::_font);
    esc_text.setString("esc - exit\np - pause");
    esc_text.setCharacterSize(matrix[0][0]._size);
    esc_text.setFillColor(sf::Color(0, 255, 0, 128));

    // background for esc_text
    sf::FloatRect backgroundRect = esc_text.getLocalBounds();
    sf::RectangleShape background(sf::Vector2f(backgroundRect.width, backgroundRect.height));
    background.setFillColor(sf::Color::Black);

    //int loops_counter = 0;
    //setFramerateLimit
    window.setFramerateLimit(10);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed
                && event.key.code == sf::Keyboard::Escape)
                window.close();
            if (event.type == sf::Event::KeyPressed
                && event.key.code == sf::Keyboard::P)
            {
                cout << "Pause" << endl;
                
                // wait for another push to P-button
                while (true) {
                    window.pollEvent(event);
                    if (event.type == sf::Event::KeyPressed
                        && event.key.code == sf::Keyboard::P)
                        break;
                }
            }
        }

        window.clear();
        drawMatrix(matrix, window);
        window.draw(background, esc_text.getTransform());
        window.draw(esc_text);
        window.display();
        //std::this_thread::sleep_for(std::chrono::milliseconds(50));

        // updating matrix of Letters
        moveMatrixOfLetters(matrix);
        createNewLayer(matrix);
        makeAlphaRain(matrix);

        // This code is for screenshots:
        //if (loops_counter % 100 == 0) {
        //    sf::Texture texture;
        //    texture.create(window.getSize().x, window.getSize().y);
        //    texture.update(window);
        //    string filename = "PrtSc";
        //    filename += std::to_string(loops_counter);
        //    filename += ".jpg";
        //    cout << filename << endl;
        //    if (texture.copyToImage().saveToFile(filename))
        //    {
        //        std::cout << "screenshot saved to " << filename << std::endl;
        //    }
        //}
        //loops_counter++;
    }*/

    return 0;
}
