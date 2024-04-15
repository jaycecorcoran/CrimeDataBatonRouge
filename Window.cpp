//
// Created by thoma on 4/15/2024.
//

#include "Window.h"
#include <iostream>

Window::~Window() {}

TitleWindow::TitleWindow() : window(sf::VideoMode(800, 600), "Food Waste Visualization") {
    if (!font.loadFromFile("font.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

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
    window.clear(sf::Color::White);

    sf::Text title("Visualization of the US food waste crisis", font, 24);
    title.setFont(font);
    title.setPosition(200, 50);
    title.setFillColor(sf::Color::Black);
    window.draw(title);

    sf::Text teamInfo("THE FOOD WASTERS \n Thomas Chappell, Jayce Corcoran, Caleb Jackson", font, 20);
    teamInfo.setPosition(300, 150);
    teamInfo.setFillColor(sf::Color::Black);
    window.draw(teamInfo);

    window.display();
}