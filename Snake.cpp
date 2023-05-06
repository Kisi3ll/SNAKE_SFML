#include <iostream>
#include "Snake.h"
#include "Board.h"
#include <cstring>

Snake::Snake() {
    score = 0;
    pressedKey = 72;
    headRotate = RIGHT;//TODO static_cast<Direction>(rand() % 4);
    length = 10;
    speed = 5;
    for(int i=0;i<length;++i){
        snakePoss.push_back({300, 300+i});
    }
    snake = sf::RectangleShape(sf::Vector2f(20, 20));
    snake.setPosition(280, 300);
    snake.setFillColor(sf::Color::Yellow);//TODO less color when growing
}

void Snake::headRotateFunc(int &key) {
    lastHeadRotate = headRotate;
    if (pressedKey != key) {
        if((key == 71 && lastHeadRotate != RIGHT) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && lastHeadRotate != RIGHT)) {//TODO WSAD controll
            headRotate = LEFT;
        }
        if((key == 72 && lastHeadRotate != LEFT) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && lastHeadRotate != LEFT)) {
            headRotate = RIGHT;
        }
        if((key == 73 && lastHeadRotate != DOWN) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && lastHeadRotate != DOWN)) {
            headRotate = UP;
        }
        if((key == 74 && lastHeadRotate != UP) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && lastHeadRotate != UP)) {
            headRotate = DOWN;
        }
    }
    pressedKey = key;
}

void Snake::update() {
    int x = snakePoss[0].first;
    int y = snakePoss[0].second;
    switch (headRotate) {
        case UP:
            y--;
            snakePoss.pop_back();
            snakePoss.insert(snakePoss.begin()+1, {x, y});
            break;
        case DOWN:
            y++;
            snakePoss.pop_back();
            snakePoss.insert(snakePoss.begin()+1, {x, y});
            break;
        case LEFT:
            x--;
            snakePoss.pop_back();
            snakePoss.insert(snakePoss.begin()+1, {x, y});
            break;
        case RIGHT:
            x++;
            snakePoss.pop_back();
            snakePoss.insert(snakePoss.begin()+1, {x, y});
            break;
    }
    checkEdges();

    if(headRotate == LEFT){
        snakePoss[0].first -= speed;
    }
    if(headRotate == RIGHT){
        snakePoss[0].first += speed;
    }
    if(headRotate == UP){
        snakePoss[0].second -= speed;
    }
    if(headRotate == DOWN){
        snakePoss[0].second += speed;
    }
}

void Snake::checkEdges() {
    if(snakePoss[0].second > 600){
        if(Mode != HARD){
            snakePoss[0].second = 0;
        }
        else{
            State = FINISHED;
        }
    }
    if(snakePoss[0].first > 800){
        if(Mode != HARD){
            snakePoss[0].first = 0;
        }
        else{
            State = FINISHED;
        }
    }
    if(snakePoss[0].second < 0){
        if(Mode != HARD){
            snakePoss[0].second = 600;
        }
        else{
            State = FINISHED;
        }
    }
    if(snakePoss[0].first < 0){
        if(Mode != HARD){
            snakePoss[0].first = 800;
        }
        else{
            State = FINISHED;
        }
    }
}

void Snake::drawSnake(sf::RenderWindow &win) {
    for(int i=0;i<length;i++){
        checkCollisionsFood();
        if(snakePoss[i].first == snakePoss[length-1].first && snakePoss[i].second == snakePoss[length-1].second && length >200){
            State = FINISHED;
        }
        else{
            snake.setPosition(snakePoss[i].first, snakePoss[i].second);
            win.draw(snake);
        }
    }
}

void Snake::checkCollisionsFood() {
    int vectorSize = foodVector.size();
    int maxPosX, maxPosY, minPosX, minPosY;
    for(int i=0;i<vectorSize;i++){
        if(snakePoss[0].first > foodVector[i].foodPositionX){
            maxPosX = snakePoss[0].first;
            minPosX = foodVector[i].foodPositionX;
        }
        else{
            minPosX = snakePoss[0].first;
            maxPosX = foodVector[i].foodPositionX;
        }

       if(snakePoss[0].second > foodVector[i].foodPositionY){
           maxPosY = snakePoss[0].second;
           minPosY = foodVector[i].foodPositionY;
       }
       else{
           minPosY = snakePoss[0].second;
           maxPosY = foodVector[i].foodPositionY;
       }

       if(maxPosX - minPosX < 20 && maxPosY - minPosY < 20){
           if(foodVector[i].foodType == NORM){
               length += 5;
               ++score;
           }
           if(foodVector[i].foodType == SPECIAL){
               if(health > 0){
                   health -= 1;
               }
               else{
                   setState(FINISHED);
               }
           }
           if(headRotate == UP){
               snakePoss.push_back({snakePoss[length-1].first, snakePoss[length-1].second+5});
           }
           if(headRotate == DOWN){
               snakePoss.push_back({snakePoss[length-1].first, snakePoss[length-1].second-5});
           }
           if(headRotate == LEFT){
               snakePoss.push_back({snakePoss[length-1].first+5, snakePoss[length-1].second});
           }
           if(headRotate == RIGHT){
               snakePoss.push_back({snakePoss[length-1].first-5, snakePoss[length-1].second});
           }
           addFood();
           removeFood(i);
       }
    }
}