//
// Created by thoma on 4/16/2024.
//

#ifndef PROG3_ZIPWINDOW_H
#define PROG3_ZIPWINDOW_H

#include <SFML/Graphics.hpp>

class ZipWindow {
public:
    ZipWindow(const std::string& zipCode);
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::RectangleShape button1;
    sf::RectangleShape button2;
    sf::Texture buttonTexture;
    sf::Text buttonText1;
    sf::Text buttonText2;

    void handleEvents();
    void draw();
};

#endif //PROG3_ZIPWINDOW_H
