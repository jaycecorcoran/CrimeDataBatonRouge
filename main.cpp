//FoodWasters project
#include <SFML/graphics.hpp>
#include <iostream>
#include "Window.h"
using namespace std;

int main() {
    cout << "hello" << endl;

    /*
    //SFML test from minesweeper project
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            window.clear();
            window.draw(shape);
            window.display();
        }
    }
    return 0;
     */

    TitleWindow titleWindow;
    titleWindow.run();

    return 0;
}

