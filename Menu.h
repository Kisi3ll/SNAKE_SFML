#ifndef SNAKE_SFML_MENU_H
#define SNAKE_SFML_MENU_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Snake.h"

class Menu : public Snake {
protected:
    sf::Font font;
    sf::Text text;
    sf::Text backButton;
    sf::Color borderColor;
    std::vector<sf::Text> textVec;
    sf::Text textScore;
    sf::Text textHealth;
    sf::Text scoreNum;
    sf::Text healthNum;
    sf::Texture snakeLogo;
    sf::Sprite snakeSprite;

public:
    explicit Menu(GameMode & mode);
    static std::string getStringMode(GameMode & mode);
    void startScreen();
    void settings();
    void setState(int & state);
};


#endif //SNAKE_SFML_MENU_H
