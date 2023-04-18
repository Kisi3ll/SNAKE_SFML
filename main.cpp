#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "SFMLController.h"

int main() {
    srand(time(0));
    const int screenWidth = 800;
    const int screenHeight = 600;
    sf::RenderWindow win(sf::VideoMode(screenWidth, screenHeight), "Snake");
    win.setVerticalSyncEnabled(true);

    SFMLController map(NORMAL);
    while (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                win.close();
            }
            map.handleEvent(event);
        }
        if (map.getState() == RUNNING) {
            win.clear(sf::Color::Black);
        }
        else {
            win.clear(sf::Color::White);
        }
        map.drawMenu(win);
        win.display();
    }
    return 0;
}