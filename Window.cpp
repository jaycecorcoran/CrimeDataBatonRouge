//
// Created by thoma on 4/15/2024.
//

#include "Window.h"
#include <iostream>

Window::~Window() {}

TitleWindow::TitleWindow() : window(sf::VideoMode(1200, 900), "Food Waste Visualization") {
    if (!font.loadFromFile("Lato-Black.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    if (!foodTexture.loadFromFile("food.png")) {
        std::cerr << "Failed to load food image" << std::endl;
    }

    // Set up the food sprite
    foodSprite.setTexture(foodTexture);

    title.setFont(font);
    title.setString("Visualization of the US food waste crisis");
    title.setCharacterSize(36);
    title.setFillColor(sf::Color::Black);

    // Initialize team information text
    teamInfo.setFont(font);
    teamInfo.setString("THE FOOD WASTERS \n Thomas Chappell, Jayce Corcoran, Caleb Jackson");
    teamInfo.setCharacterSize(24);
    teamInfo.setFillColor(sf::Color::Black);
}

void TitleWindow::run() {
    while (window.isOpen()) {
        handleEvents();
        draw();
    }
}

void TitleWindow::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void TitleWindow::draw() {
    window.clear(sf::Color(255, 165, 0)); // Orange background

    // Calculate center positions for the text
    float centerX = window.getSize().x / 2.0f;
    float centerY = window.getSize().y / 2.0f;

    // Draw white boxes behind the text (omitted for brevity)

    // Title text
    title.setPosition(centerX - title.getLocalBounds().width / 2, 50); // Center horizontally
    window.draw(title);

    // Team information text
    teamInfo.setPosition(centerX - teamInfo.getLocalBounds().width / 2, centerY - teamInfo.getLocalBounds().height / 2); // Center horizontally and vertically
    window.draw(teamInfo);

    sf::FloatRect titleBounds = title.getGlobalBounds();
    sf::FloatRect teamInfoBounds = teamInfo.getGlobalBounds();
    float imageX = centerX - foodSprite.getLocalBounds().width / 2;
    float imageY = titleBounds.top + titleBounds.height + 20; // Place the image 20 pixels below the title text
    foodSprite.setPosition(imageX, imageY);
    window.draw(foodSprite);

    window.display(); // Display the window contents
}
