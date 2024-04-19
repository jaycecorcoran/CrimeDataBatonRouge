//
// Created by thoma on 4/16/2024.
//

#include "ZipWindow.h"
#include <iostream>

ZipWindow::ZipWindow(const std::string& zipCode) : window(sf::VideoMode(1200, 900), zipCode + " Data Visualization"), zipCode(zipCode) {
    loadFont();
    loadBackgroundImage();
    setupTitleText();
    setupCommonCrimesText();
    setupCrimeTexts();
}

void ZipWindow::run() {
    while (window.isOpen()) {
        handleEvents();
        draw();
    }
}

void ZipWindow::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void ZipWindow::draw() {
    window.clear(sf::Color(255, 165, 0)); // Orange background

    // Draw background image
    backgroundImage.setScale(0.55f, 0.55f);
    backgroundImage.setPosition((window.getSize().x - backgroundImage.getLocalBounds().width * 0.55f) / 2.f, 100.f);
    window.draw(backgroundImage);

    // Draw title text
    window.draw(titleText);

    // Draw common crimes text
    window.draw(commonCrimesText);

    // Draw crime texts
    for (const auto& text : crimeTexts) {
        window.draw(text);
    }

    window.display();
}

void ZipWindow::loadBackgroundImage() {
    if (!backgroundImageTexture.loadFromFile("BatonRouge.jpg")) {
        std::cerr << "Failed to load background image" << std::endl;
    }
    backgroundImage.setTexture(backgroundImageTexture);

}

void ZipWindow::loadFont() {
    if (!font.loadFromFile("Lato-Black.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
}

void ZipWindow::setupTitleText() {
    titleText.setFont(font);
    titleText.setString("Data for Zip Code " + zipCode);
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = titleText.getLocalBounds();
    titleText.setPosition((window.getSize().x - textBounds.width) / 2.f, 20);
}

void ZipWindow::setupCommonCrimesText() {
    commonCrimesText.setFont(font);
    commonCrimesText.setString("5 Most Common Crimes in " + zipCode + ":");
    commonCrimesText.setCharacterSize(30);
    commonCrimesText.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = commonCrimesText.getLocalBounds();
    commonCrimesText.setPosition((window.getSize().x - textBounds.width) / 2.f, 550.f);
}

void ZipWindow::setupCrimeTexts() {
    // Set up crime texts
    const std::vector<std::string> crimeNames = {"Crime 1", "Crime 2", "Crime 3", "Crime 4", "Crime 5"};
    const float startY = 610.f;
    const float lineHeight = 40.f;
    for (size_t i = 0; i < crimeNames.size(); ++i) {
        sf::Text crimeText;
        crimeText.setFont(font);
        crimeText.setString(std::to_string(i + 1) + ". " + crimeNames[i]);
        crimeText.setCharacterSize(24);
        crimeText.setFillColor(sf::Color::Black);
        crimeText.setPosition(450.f, startY + i * lineHeight);
        crimeTexts.push_back(crimeText);
    }
}


