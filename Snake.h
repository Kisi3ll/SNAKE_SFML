#ifndef SNAKE_SFML_SNAKE_H
#define SNAKE_SFML_SNAKE_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Board.h"

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

//struct snakeBody {
//    int xPos;
//    int yPos;
//    Direction dir;
//};


class Snake : public Board {
protected:
    int speed;
    int pressedKey;
    std::vector<std::pair <int, int>> snakePoss;
    int length;
    int score;

    Direction headRotate;
    Direction lastHeadRotate;
    std::vector<int> positionX;
    std::vector<int> positionY;
    std::vector<sf::Vector2i> poss;
    sf::RectangleShape snake;

public:
    Snake();
    void headRotateFunc(int & key);
    void checkEdges();
    void checkCollisionsFood();
    void drawSnake(sf::RenderWindow & win);
    void update();
};


#endif //SNAKE_SFML_SNAKE_H
