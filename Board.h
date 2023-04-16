#ifndef SNAKE_SFML_BOARD_H
#define SNAKE_SFML_BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>

enum FoodType{
    NORM,
    SPECIAL
};
enum GameMode{
    EASY,
    NORMAL,
    HARD
};
enum GameState{
    RUNNING,
    SETTINGS,
    START_SCREEN,
    FINISHED
};

struct Food{
    int foodPositionX;
    int foodPositionY;
    FoodType foodType;
};

class Board {
protected:
    GameMode Mode;
    GameState State;
    GameState LastState;
    Food food;
    int time;
    int sTime;
    int foodCount;
    int health;
    sf::Texture appleTexture;
    sf::Sprite appleSprite;
    sf::Texture bombTexture;
    sf::Sprite bombSprite;
    sf::RectangleShape line[4];
    std::vector<Food> foodVector;
    sf::Color borderColor;

public:
    Board();
    void addFood();
    void removeFood(int position = 1);
    void drawFood(sf::RenderWindow & win);
    int countOfFood();
    virtual void setState(GameState state);
    GameState getState() const;
};


#endif //SNAKE_SFML_BOARD_H
