#include <iostream>
#include "Board.h"
#include "Menu.h"
#include <cstring>

Board::Board() {
    if(!appleTexture.loadFromFile("../Image/apple.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if(!bombTexture.loadFromFile("../Image/bomb.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }

    line[0] = sf::RectangleShape(sf::Vector2f(800, 5));
    line[1] = sf::RectangleShape(sf::Vector2f(5, 600));
    line[1].setPosition(795, 0);
    line[2] = sf::RectangleShape(sf::Vector2f(800, 5));
    line[2].setPosition(0, 595);
    line[3] = sf::RectangleShape(sf::Vector2f(5, 800));
    borderColor = sf::Color::Green;

    appleSprite.setTexture(appleTexture);
    bombSprite.setTexture(bombTexture);
    time = 0;
    foodCount = 0;
    sTime = 0;
    health = 3;
}

void Board::addFood() {
    if(foodCount > countOfFood()) {
        removeFood();
        addFood();
    }
    else {
        food.foodPositionX = rand() % 770 + 10;
        food.foodPositionY = rand() % 570 + 10;

        if(Mode == EASY) {
            food.foodType = NORM;
        }
        if(Mode == HARD || Mode == NORMAL) {
            if(rand() % 3 == 1) {
                food.foodType = SPECIAL;
            } else {
                food.foodType = NORM;
            }
        }
        foodVector.push_back(food);
        ++foodCount;
    }
}

void Board::removeFood(int position) {
    if(State != RUNNING) {
        foodCount = 0;
        foodVector.clear();
    }
    else{
        --foodCount;
        foodVector.erase(foodVector.begin() + position);
    }
}

void Board::drawFood(sf::RenderWindow &win) {
    for(int i=0;i<foodCount;++i) {
        if(foodVector[i].foodType == NORM){
            appleSprite.setPosition(foodVector[i].foodPositionX, foodVector[i].foodPositionY);
            win.draw(appleSprite);
        }
        if(foodVector[i].foodType == SPECIAL){
            bombSprite.setPosition(foodVector[i].foodPositionX, foodVector[i].foodPositionY);
            win.draw(bombSprite);
        }
    }
}

void Board::setState(GameState state) {
    if(State != SETTINGS){
        LastState = State;
        State = state;
    }
}

GameState Board::getState() const {
    return State;
}

int Board::countOfFood() {
    if(Mode == EASY) {
        return 2;
    }
    if(Mode == NORMAL) {
        return 4;
    }
    if(Mode == HARD) {
        return 6;
    }
    return 0;
}
