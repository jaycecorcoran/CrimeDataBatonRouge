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
    std::string zipCode; // New member variable to hold the zip code
    sf::Text titleText;
    sf::Text commonCrimesText;
    sf::Texture backgroundImageTexture;
    sf::Sprite backgroundImage;
    std::vector<sf::Text> crimeTexts;

    void handleEvents();
    void draw();
    void loadBackgroundImage();
    void loadFont();
    void setupTitleText();
    void setupCommonCrimesText();
    void setupCrimeTexts();
};

#endif //PROG3_ZIPWINDOW_H
