//
// Created by thoma on 4/18/2024.
//

#ifndef PROG3_CITYWINDOW_H
#define PROG3_CITYWINDOW_H

#include <SFML/Graphics.hpp>
#include "Heaps.h"
#include "Hashtable.h"
#include <iostream>
#include <chrono>

using namespace std::chrono;

class CityWindow {
public:
    CityWindow(const std::string& structureType, heap, Hashtable);
    void run();

private:
    heap heap;
    Hashtable hashtable;
    std::string dataStructureType;
    sf::RenderWindow window;
    sf::Font font;
    sf::Text titleText;
    sf::Texture backgroundImageTexture;
    sf::Sprite backgroundImage;
    sf::Text crimeRateText;
    std::vector<sf::Text> crimeRateRows;

    void handleEvents();
    void draw();
    void loadBackgroundImage();
    void loadFont();
    void setupTitleText();
    void setupCrimeRateText();
    void setupCrimeRateRows();
    // Function for listing values from the heap (to be implemented)
    // Function for listing values from the hashtable (to be implemented)
};

#endif //PROG3_CITYWINDOW_H
