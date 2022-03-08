#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const float GRAVITY = 9.8f;
const float MAX_DELTA_Y = 2.150f;
const size_t ALPHABET_CAPACITY = 25;
const int MAX_LIFE_TIME_SEC = 30;
const int RAIN_LENGTH = 10;

class Letter {
public:
    char _letter = 'a' + rand() % ALPHABET_CAPACITY;;
    int _size = 15;// 15;
    int _size_x = 12;//12;// 25;
    int _size_y = 12;//12;// 25;
    int _alpha = rand() % 255;
    int _live_time = rand() % MAX_LIFE_TIME_SEC;

    int _pos_x = 0;
    int _pos_y = 0;

    static sf::Font _font;
    sf::Text _text;
    Letter() {
        _text.setFont(_font);
        _text.setCharacterSize(_size);//TEMP
        _text.setFillColor(sf::Color(0, 255, 0, _alpha));
        _text.setString(_letter);
        _text.setPosition(0, 0);
        _text.move(_pos_x, _pos_y);
    }
    Letter(const Letter& other) {
        _letter = other._letter;
        _size = other._size;
        _size_x = other._size_x;
        _size_y = other._size_y;
        _alpha = other._alpha;
        _live_time = other._live_time;

        // position will stay the same
        //_pos_x = other._pos_x;
        //_pos_y = other._pos_y;

        _text = other._text;
        _text.move(0, _size_y);
    }
    void update_text() {
        //_text.setCharacterSize(_size);
        sf::Color tmp = _text.getFillColor();
        tmp.a = _alpha;
        _text.setFillColor(tmp);
        _text.setOutlineColor(sf::Color(0, 0, 0, 0));//TEMP
        _text.setString(_letter);
        _text.setPosition(0, 0);
        _text.move(_pos_x, _pos_y);
    }
    void drawFallingLetter(sf::RenderWindow& window) {
        window.draw(_text);
    }
    void moveFallingLetter(sf::RenderWindow& window, float sec) {
        //float half_window_y = window.getSize().y / 2;
        //        float delta_time = (sec - this->time);
        //        this->time = sec;
        //        
        //        float curr_y = y_0;
        //        if ((GRAVITY * sec) * delta_time < MAX_DELTA_Y) {
        //            //curr_y += GRAVITY * sec * sec / 2.0f;
        //            
        //            curr_y += (GRAVITY * sec) * delta_time;
        //            cout << (GRAVITY * sec) * delta_time << endl;
        //        }
        //        else {
        //            curr_y += MAX_DELTA_Y;
        //            cout << (GRAVITY * sec) * delta_time << endl;
        //        }
        //        y_0 = curr_y;
        //
        //        while (curr_y > half_window_y) {
        //            curr_y -= half_window_y;
        //            this->setLetter(' ' + rand() % ALPHABET_CAPACITY);
        //            sf::Vector2f offset(rand() % window.getSize().x, 0);
        //            this->setPosition(offset);
        //            this->setSize(20 + rand() % 40);
        //        }
        //        
        //        Uint8 curr_alpha = 255 * (half_window_y - curr_y) / half_window_y;
        //        _text.setFillColor(sf::Color(0, 255, 0, curr_alpha));
        //        _text.setPosition(sf::Vector2f(_text.getPosition().x, curr_y));
        //        window.draw(_text);
    }
    
};

void createNewLaeyer(std::vector<vector<Letter>>& matrix) {
    cout << "createNewLaeyer" << endl;
    for (int x = 0; x < matrix.size(); x++) {
        int y = 0;
        matrix[x][y] = Letter();
        // init position of each letter
        matrix[x][y]._pos_x = x * matrix[x][y]._size_x;
        matrix[x][y]._pos_y = y * matrix[x][y]._size_y;

        matrix[x][y].update_text();
        if (matrix[x][0]._alpha >= 240) {
            matrix[x][0]._alpha = 255;
            matrix[x][0]._text.setFillColor(sf::Color(255, 0, 0, matrix[x][0]._alpha));//RED
        }
    }
}

void moveMatrixOfLetters(std::vector<vector<Letter>>& matrix) {
    cout << "moveMatrixOfLetters" << endl;
    for (int x = 0; x < matrix.size(); x++) {
        for (int y = matrix[0].size() - 1; y > 0; y--) {
            int pos_x = matrix[x][y]._pos_x;
            int pos_y = matrix[x][y]._pos_y;
            matrix[x][y] = Letter(matrix[x][y - 1]);
            //matrix[x][y]._text = matrix[x][y - 1]._text;
        }
        //matrix[x][0] = Letter();
    }
}

void makeAlphaRain(std::vector<vector<Letter>>& matrix) {
    cout << "makeAlphaRain" << endl;
    for (int x = 0; x < matrix.size(); x++) {
        for (int y = matrix[0].size() - 1; y >= 0; y--) {
            // init alpha chanell
            if (matrix[x][y]._alpha == 255 && (int)(matrix[x][y]._text.getFillColor().r) == 255) {

                int max_alpha = 255;
                for (int _y = y; _y >= 0; _y--) {
                    matrix[x][_y]._alpha = max_alpha;
                    matrix[x][_y]._text.setFillColor(sf::Color(255, 0, 0, max_alpha));//RED
                    //cout << x << ", " << _y << endl;
                    if (max_alpha - 255 / RAIN_LENGTH >= 0)
                        max_alpha -= 255 / RAIN_LENGTH;
                    else {
                        max_alpha = 0;
                        break;
                    }     
                }
            }
        }
    }
}

sf::Font createFont()
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        exit(-1);
    }
    return font;
}
sf::Font Letter::_font(createFont());

void drawMatrix(vector<vector<Letter>>& matrix, sf::RenderWindow& window) {
    for (auto line = matrix.begin(); line < matrix.end(); line++) {
        for (auto it = line->begin(); it < line->end(); it++) {
            it->drawFallingLetter(window);
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
    vector<vector<Letter>> matrix(window.getSize().x / one_letter._size_x);
    for (auto it = matrix.begin(); it < matrix.end(); ++it) {
        it->resize(window.getSize().y / one_letter._size_y);
    }

    // Initialization of start Letters
    for (int x = 0; x < matrix.size(); x++) {
        for (int y = 0; y < matrix[0].size(); y++) {
            // init alpha chanell
            //matrix[x][y]._alpha = 0;//TEMP
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
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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
        createNewLaeyer(matrix);
        makeAlphaRain(matrix);        
    }

    return 0;
}
