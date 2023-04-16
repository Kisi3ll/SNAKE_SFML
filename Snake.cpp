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

    snakePoss[0] = 300;
    snakePoss[1] = 300;
    snake = sf::RectangleShape(sf::Vector2f(20, 20));
    snake.setPosition(280, 300);
    snake.setFillColor(sf::Color::Yellow);//TODO color
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
    if(positionX.size() > length){
        positionX.erase(positionX.begin());
        positionY.erase(positionY.begin());
    }
    if(headRotate == LEFT){
        positionX.push_back(snakePoss[0]);
        positionY.push_back(snakePoss[1]);
    }
    if(headRotate == RIGHT){
        positionX.push_back(snakePoss[0]);
        positionY.push_back(snakePoss[1]);
    }
    if(headRotate == UP){
        positionX.push_back(snakePoss[0]);
        positionY.push_back(snakePoss[1]);
    }
    if(headRotate == DOWN){
        positionX.push_back(snakePoss[0]);
        positionY.push_back(snakePoss[1]);
    }
    checkEdges();

    if(headRotate == LEFT){
        snakePoss[0] -= speed;
    }
    if(headRotate == RIGHT){
        snakePoss[0] += speed;
    }
    if(headRotate == UP){
        snakePoss[1] -= speed;
    }
    if(headRotate == DOWN){
        snakePoss[1] += speed;
    }
}

void Snake::checkEdges() {
    if(snakePoss[1] > 600){
        if(Mode != HARD){
            snakePoss[1] = 0;
        }
        else{
            State = FINISHED;
        }
    }
    if(snakePoss[0] > 800){
        if(Mode != HARD){
            snakePoss[0] = 0;
        }
        else{
            State = FINISHED;
        }
    }
    if(snakePoss[1] < 0){
        if(Mode != HARD){
            snakePoss[1] = 600;
        }
        else{
            State = FINISHED;
        }
    }
    if(snakePoss[0] < 0){
        if(Mode != HARD){
            snakePoss[0] = 800;
        }
        else{
            State = FINISHED;
        }
    }
}

void Snake::drawSnake(sf::RenderWindow &win) {
    for(int i=0;i<length;i++){
        checkCollisionsFood();
        if(positionX[i] == positionX[length] && positionY[i] == positionY[length] && length >100){
            State = FINISHED;
        }
        else{
            snake.setPosition(positionX[i], positionY[i]);
            win.draw(snake);
        }
    }
}

void Snake::checkCollisionsFood() {
    int vectorSize = Board::foodVector.size();
    int maxPosX, maxPosY, minPosX, minPosY;
    for(int i=0;i<vectorSize;i++){
       if(positionX[length] > foodVector[i].foodPositionX){
           maxPosX = positionX[length];
           minPosX = foodVector[i].foodPositionX;
       }
       else{
           minPosX = positionX[length];
           maxPosX = foodVector[i].foodPositionX;
       }

       if(positionY[length] > foodVector[i].foodPositionY){
           maxPosY = positionY[length];
           minPosY = foodVector[i].foodPositionY;
       }
       else{
           minPosY = positionY[length];
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
                   length -= 1;
               }
               else{
                   setState(FINISHED);
               }
           }
           addFood();
           removeFood(i);
       }
    }
}