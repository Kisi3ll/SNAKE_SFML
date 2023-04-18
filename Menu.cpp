#include <iostream>
#include "Menu.h"
#include <cstring>

Menu::Menu(GameMode & mode) {
    //std::cout << "Menu created" << std::endl;
    Mode = mode;
    State = START_SCREEN;
    if (!font.loadFromFile("../Font/Arcade.ttf")) {
        std::cerr<<strerror(errno)<<std::endl;
        abort();
    }
    if (!snakeLogo.loadFromFile("../Image/snake.png")) {
        std::cerr<<strerror(errno)<<std::endl;
        abort();
    }
    startScreen();

    backButton.setFont(font);
    backButton.setFillColor(sf::Color::Blue);
    backButton.setString("GoBack");
    backButton.setPosition(10, 10);

    textScore.setFont(font);
    textScore.setFillColor(sf::Color::White);
    textScore.setString("Score: ");
    textScore.setPosition(665, 10);

    textHealth.setFont(font);
    textHealth.setFillColor(sf::Color::White);
    textHealth.setString("Health: ");
    textHealth.setPosition(515, 10);

    scoreNum.setFont(font);
    scoreNum.setFillColor(sf::Color::White);
    scoreNum.setPosition(760, 10);

    healthNum.setFont(font);
    healthNum.setFillColor(sf::Color::White);
    healthNum.setPosition(620, 10);
}

std::string Menu::getStringMode(GameMode & mode) {
    switch (mode) {
        case EASY:
            return "EASY";
        case NORMAL:
            return "NORMAL";
        case HARD:
            return "HARD";
    }
}

void Menu::startScreen() {
    snakeSprite.setTexture(snakeLogo);
    snakeSprite.setPosition(190, 0);

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString("START");
    text.setPosition(360, 300);

    textVec.push_back(text);

    text.setFillColor(sf::Color::Black);
    text.setString("SETTINGS");
    text.setPosition(335, 350);

    textVec.push_back(text);

    text.setFillColor(sf::Color::Black);
    text.setString("MODE: " + getStringMode(Mode));
    text.setPosition(310, 555);

    textVec.push_back(text);
}

void Menu::settings() {
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString("SELECT MODE: ");
    text.setPosition(330, 255);

    textVec.push_back(text);

    text.setFillColor(sf::Color::Yellow);
    text.setString("EASY");
    text.setPosition(350, 300);

    textVec.push_back(text);

    text.setFillColor(sf::Color::Magenta);
    text.setString("NORMAL");
    text.setPosition(350, 350);

    textVec.push_back(text);

    text.setFillColor(sf::Color::Red);
    text.setString("HARD");
    text.setPosition(350, 400);

    textVec.push_back(text);

    text.setFillColor(sf::Color::Black);
    text.setString("MODE: " + getStringMode(Mode));
    text.setPosition(310, 555);

    textVec.push_back(text);
}

void Menu::setState(int &state) {
    if(State == SETTINGS) {
        Mode = static_cast<GameMode>(state);//static_cast() converting int to enum
        //State = LastState;
        if(Mode == EASY){
            speed = 3;
            snake.setFillColor(sf::Color::Yellow);
            borderColor = sf::Color::Yellow;
        }
        if(Mode == NORMAL){
            speed = 4;
            snake.setFillColor(sf::Color::Magenta);
            borderColor = sf::Color::Magenta;
        }
        if(Mode == HARD){
            speed = 5;
            snake.setFillColor(sf::Color::Red);
            borderColor = sf::Color::Red;
        }
    }
    else{
        LastState = State;
        State = static_cast<GameState>(state);//static_cast() converting int to enum
    }
}