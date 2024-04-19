//
// Created by thoma on 4/16/2024.
//

#include "ZipWindow.h"
#include <iostream>

ZipWindow::ZipWindow(const std::string& zipCode) : window(sf::VideoMode(1200, 900), zipCode + " Data Visualization") {
    if (!font.loadFromFile("Lato-Black.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    if (!buttonTexture.loadFromFile("tile_hidden.png")) {
        std::cerr << "Failed to load button texture";
    }

    // Set up buttons
    button1.setSize(sf::Vector2f(200, 60));
    button1.setTexture(&buttonTexture);
    button1.setPosition(300, 800);

    button2.setSize(sf::Vector2f(200, 60));
    button2.setTexture(&buttonTexture);
    button2.setPosition(700, 800);

    // Set up button text
    buttonText1.setFont(font);
    buttonText1.setString("Graph 1");
    buttonText1.setCharacterSize(24);
    buttonText1.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds1 = buttonText1.getLocalBounds();
    buttonText1.setPosition(button1.getPosition().x + (button1.getSize().x - textBounds1.width) / 2, button1.getPosition().y + (button1.getSize().y - textBounds1.height) / 2);

    buttonText2.setFont(font);
    buttonText2.setString("Graph 2");
    buttonText2.setCharacterSize(24);
    buttonText2.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds2 = buttonText2.getLocalBounds();
    buttonText2.setPosition(button2.getPosition().x + (button2.getSize().x - textBounds2.width) / 2, button2.getPosition().y + (button2.getSize().y - textBounds2.height) / 2);
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

    // Draw buttons and button text
    window.draw(button1);
    window.draw(button2);
    window.draw(buttonText1);
    window.draw(buttonText2);

    window.display();
}
