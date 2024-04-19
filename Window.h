//
// Created by thoma on 4/15/2024.
//

#ifndef PROG3_WINDOW_H
#define PROG3_WINDOW_H

#include <SFML/Graphics.hpp>

class Window {
public:
    virtual ~Window() = 0;
    virtual void run() = 0;
};

class TitleWindow : public Window {
public:
    TitleWindow();
    virtual void run() override;

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text title;
    sf::Text teamInfo;
    sf::Texture criminalTexture;
    sf::Sprite criminalSprite;

    sf::RectangleShape button1;
    sf::RectangleShape button2;
    sf::Texture buttonTexture;
    sf::Text buttonText1;
    sf::Text buttonText2;

    sf::RectangleShape searchBar;
    sf::Text searchInput;

    sf::Text zipTextLabel;
    sf::Text cityTextLabel;

    void handleEvents();
    void draw();
};


#endif //PROG3_WINDOW_H
