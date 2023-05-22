#include "Letter.h"
#include "Matrix.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <cassert>

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

sf::Text initPromptText();
sf::RectangleShape initPromptRectangle(const sf::Text& esc_text);

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
    
    Matrix<Letter> matrix(numLettersX, window.getSize().y / one_letter.getSizeY());
    
    // Initialization of start Letters
    matrix.initialization();
    
    sf::Text escText = initPromptText();
    sf::RectangleShape background = initPromptRectangle(escText);

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
        matrix.drawMatrix(window);
        window.draw(background, escText.getTransform());
        window.draw(escText);
        window.display();
        //std::this_thread::sleep_for(std::chrono::milliseconds(50));

        // updating matrix of Letters
        matrix.moveMatrixOfLetters();
        matrix.createNewLayer();
        matrix.makeAlphaRain();

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
    }

    return 0;
}

sf::Text initPromptText() {
    // text that must be shown all the time
    // Text:
    //esc - exit\n
    //p - pause
    Text esc_text;
    esc_text.setFont(Letter::_font);
    esc_text.setString("esc - exit\np - pause");
    const int infoSize = 15;
    esc_text.setCharacterSize(infoSize);
    esc_text.setFillColor(sf::Color(0, 255, 0, 128));
    return esc_text;
}

sf::RectangleShape initPromptRectangle(const sf::Text& esc_text) {
    // background for esc_text
    sf::FloatRect backgroundRect = esc_text.getLocalBounds();
    sf::RectangleShape background(sf::Vector2f(backgroundRect.width, backgroundRect.height));
    background.setFillColor(sf::Color::Black);
    return background;
}