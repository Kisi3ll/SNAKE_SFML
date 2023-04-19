#include <iostream>
#include "SFMLController.h"
#include "Board.h"
#include <sstream>

SFMLController::SFMLController(GameMode mode) : Menu(mode) {
    timeTo = 0;
    isReset = true;
}

void SFMLController::drawMenu(sf::RenderWindow &win) {
    textVec.clear();
    if(State != RUNNING) {
        win.draw(snakeSprite);
    }
    if(State == RUNNING || State == FINISHED){
        if(score < 0){
            State = FINISHED;
        } else {
            std::stringstream stringNum, stringHealth;
            stringNum<<score<<std::endl;
            stringHealth<<health<<std::endl;
            scoreNum.setString(stringNum.str());
            healthNum.setString(stringHealth.str());
        }
        win.draw(textScore);
        win.draw(scoreNum);
        if(Mode != EASY && State == RUNNING){
            win.draw(textHealth);
            win.draw(healthNum);
        }
        if(State != FINISHED){
            drawGameplay(win);
        }
        else {//end game text
            textScore.setString("Your score: ");
            textScore.setFillColor(sf::Color::Black);
            textScore.setPosition(290, 300);
            scoreNum.setFillColor(sf::Color::Black);
            scoreNum.setPosition(455,300);
        }
    }
    if(State != START_SCREEN) {
        win.draw(backButton);
    }
    if(State == START_SCREEN) {
        startScreen();
    }
    if(State == SETTINGS) {
        settings();
    }
    for(const auto &_text : textVec) {//auto ignores refferences! with const is more effective
        win.draw(_text);
    }
    // the same for loop
//    for(std::vector<sf::Text>::iterator it = textVec.begin(); it != textVec.end(); ++it) {
//        win.draw(*it);
//    }
}

void SFMLController::drawGameplay(sf::RenderWindow &win) {
    for(auto &rect : line) { //same situation as upper
        rect.setFillColor(borderColor);
        win.draw(rect);
    }
    isReset = false;
    update();
    drawSnake(win);
    timeTo = (clock() - sTime);
    if(timeTo > timeToFood()) {
       addFood();
       sTime = clock();
    }
    drawFood(win);
}

void SFMLController::handleEvent(sf::Event &event) {
    if(event.type == sf::Event::MouseButtonPressed){
        int tmp = positionY(event.mouseButton.y);
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;
        if(x < 100 && y < 45){
            State = START_SCREEN;
            if(!isReset) {
                reset();
                //isReset = true;
            }
        }
        else if(x > 328 && x < 512 && y > 304 && y < 436){
            setState(tmp);
        }
    }
    if(event.type == sf::Event::KeyPressed && State == RUNNING){
        int key = event.key.code;
        headRotateFunc(key);
        //headRotateFunc(static_cast<int &>(event.key.code));//TODO its works correctly?
    }
}

int SFMLController::positionY(int y) {//dont work full correnctly
    y -= 300; //middle of the screen
    for(int i=0;i<3;++i){
        if(y<20 && y>0){
            return i;
        } else {
            y -= 50;
        }
    }
    return 2;
}

void SFMLController::reset() {
    score = 0;
    length = 10;
    health = 3;
    pressedKey = 72;
    headRotate = RIGHT;//TODO static_cast<Direction>(rand() % 4);

    Snake::snakePoss[0] = 300;
    Snake::snakePoss[1] = 300;
    Snake::positionX.clear();
    Snake::positionY.clear();
    Board::removeFood();

    textScore.setString("Score: ");
    textScore.setPosition(665,10);
    scoreNum.setPosition(760,10);
    scoreNum.setFillColor(sf::Color::White);

    isReset = true;
}
#ifdef __WIN32__
int SFMLController::timeToFood() {
    if(Mode == EASY){
        return 8000;
    }
    else if(Mode == NORMAL) {
        return 4000;
    }
    else if(Mode == HARD) {
        return 2000;
    }
    return -1;
}
#elif __linux__
int SFMLController::timeToFood() {
    if(Mode == EASY){
        return 400000;
    }
    else if(Mode == NORMAL) {
        return 200000;
    }
    else if(Mode == HARD) {
        return 100000;
    }
    return -1;
}
#endif
