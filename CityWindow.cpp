//
// Created by thoma on 4/18/2024.
//

#include "CityWindow.h"
#include <iostream>

CityWindow::CityWindow(const std::string& structureType) : window(sf::VideoMode(1200, 900), "City Data Visualization"), dataStructureType(structureType) {
    loadFont();
    loadBackgroundImage();
    setupTitleText();
    setupCrimeRateText();
    setupCrimeRateRows();
}

void CityWindow::run() {
    while (window.isOpen()) {
        handleEvents();
        draw();
    }
}

void CityWindow::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void CityWindow::draw() {
    window.clear(sf::Color(255, 165, 0)); // Orange background

    // Draw background image
    backgroundImage.setScale(0.55f, 0.55f);
    backgroundImage.setPosition((window.getSize().x - backgroundImage.getLocalBounds().width * 0.55f) / 2.f, 100.f);
    window.draw(backgroundImage);

    // Draw title text
    window.draw(titleText);

    // Draw crime rate text
    window.draw(crimeRateText);

    // Draw crime rate rows
    for (const auto& row : crimeRateRows) {
        window.draw(row);
    }

    window.display();
}

void CityWindow::loadBackgroundImage() {
    if (!backgroundImageTexture.loadFromFile("BatonRouge.jpg")) {
        std::cerr << "Failed to load background image" << std::endl;
    }
    backgroundImage.setTexture(backgroundImageTexture);
}

void CityWindow::loadFont() {
    if (!font.loadFromFile("Lato-Black.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
}

void CityWindow::setupTitleText() {
    titleText.setFont(font);
    titleText.setString("Baton Rouge Crime Data");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = titleText.getLocalBounds();
    titleText.setPosition((window.getSize().x - textBounds.width) / 2.f, 20.f);
}

void CityWindow::setupCrimeRateText() {
    crimeRateText.setFont(font);
    crimeRateText.setString("Zip Codes with the Highest Crime Rate:");
    crimeRateText.setCharacterSize(30);
    crimeRateText.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = crimeRateText.getLocalBounds();
    crimeRateText.setPosition((window.getSize().x - textBounds.width) / 2.f, 550.f);
}

void CityWindow::setupCrimeRateRows() {
    // get the crime info here based off heap/hashtable buttons
    if (dataStructureType == "heap") {
        //int rate1 = heap.pop()   and so on
    }
    else {
        //int rate1 = hashtable access
    }





    // Sample crime rate rows
    const std::vector<std::string> crimeRates = {"1. Rate 1", "2. Rate 2", "3. Rate 3", "4. Rate 4", "5. Rate 5"};
    const float startY = 610.f;
    const float lineHeight = 40.f;
    for (size_t i = 0; i < crimeRates.size(); ++i) {
        sf::Text row;
        row.setFont(font);
        row.setString(crimeRates[i]);
        row.setCharacterSize(24);
        row.setFillColor(sf::Color::Black);
        row.setPosition(400.f, startY + i * lineHeight);
        crimeRateRows.push_back(row);
    }
}
