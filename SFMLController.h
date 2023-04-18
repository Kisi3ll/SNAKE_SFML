#ifndef SNAKE_SFML_SFMLCONTROLLER_H
#define SNAKE_SFML_SFMLCONTROLLER_H

#include "Menu.h"
#include <SFML/Graphics.hpp>

class SFMLController : public Menu {
    long timeTo;
    bool isReset;

public:
    SFMLController(GameMode mode);
    void drawMenu(sf::RenderWindow & win);
    void drawGameplay(sf::RenderWindow & win);
    void handleEvent(sf::Event & event);
    int timeToFood();
    void reset();
    static int positionY(int y);
};

#endif //SNAKE_SFML_SFMLCONTROLLER_H
