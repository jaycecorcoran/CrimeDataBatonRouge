//
// Created by thoma on 4/15/2024.
//
#include "StateWindow.h"
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
    if (!buttonTexture.loadFromFile("tile_hidden.png")) {
        std::cerr << "Failed to load button texture";
    }

    // Set up the food sprite
    foodSprite.setTexture(foodTexture);

    title.setFont(font);
    title.setString("Visualization of the US Food Waste Crisis");
    title.setCharacterSize(36);
    title.setFillColor(sf::Color::Black);

    // Initialize team information text
    teamInfo.setFont(font);
    teamInfo.setString("                             THE FOOD WASTERS\nThomas Chappell, Jayce Corcoran, Caleb Jackson");
    teamInfo.setCharacterSize(24);
    teamInfo.setFillColor(sf::Color::Black);

    // Set up button rectangles
    button1.setSize(sf::Vector2f(200, 60)); // Adjust size as needed
    button1.setTexture(&buttonTexture);
    button1.setPosition(300, 800); // Adjust position as needed

    button2.setSize(sf::Vector2f(200, 60)); // Adjust size as needed
    button2.setTexture(&buttonTexture);
    button2.setPosition(700, 800); // Adjust position as needed

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

    searchBar.setSize(sf::Vector2f(600, 40));
    searchBar.setFillColor(sf::Color::White);
    searchBar.setOutlineThickness(2);
    searchBar.setOutlineColor(sf::Color::Black);
    searchBar.setPosition(300, 680);

    // Search input text setup
    searchInput.setFont(font);
    searchInput.setString("Please enter a state name (e.g. Texas, Florida, Oregon)");
    searchInput.setCharacterSize(20);
    searchInput.setFillColor(sf::Color::Black);
    searchInput.setPosition(305, 690);

    // Text labels setup
    stateTextLabel.setFont(font);
    stateTextLabel.setString("To view data by state:");
    stateTextLabel.setCharacterSize(20);
    stateTextLabel.setFillColor(sf::Color::Black);
    sf::FloatRect stateTextBounds = stateTextLabel.getLocalBounds();
    stateTextLabel.setPosition((window.getSize().x - stateTextBounds.width) / 2, 650);

    countryTextLabel.setFont(font);
    countryTextLabel.setString("To view data by country:");
    countryTextLabel.setCharacterSize(20);
    countryTextLabel.setFillColor(sf::Color::Black);
    sf::FloatRect countryTextBounds = countryTextLabel.getLocalBounds();
    countryTextLabel.setPosition((window.getSize().x - countryTextBounds.width) / 2, 750);
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
        } else if (event.type == sf::Event::MouseButtonPressed) {
            // Check if the mouse is clicked within the search bar
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::FloatRect searchBarBounds = searchBar.getGlobalBounds();
            if (searchBarBounds.contains(mousePos.x, mousePos.y)) {
                // Clear the search input when the search bar is clicked
                searchInput.setString("");
            }
        } else if (event.type == sf::Event::TextEntered) {
            // Handle text input
            if (event.text.unicode < 128) {
                // Check if the typed character is a backspace
                if (event.text.unicode == 8) {
                    // Remove the last character from the search input
                    std::string currentText = searchInput.getString();
                    if (!currentText.empty()) {
                        currentText.pop_back();
                        searchInput.setString(currentText);
                    }
                } else {
                    // Add typed characters to the search input
                    searchInput.setString(searchInput.getString() + static_cast<char>(event.text.unicode));
                }
            }
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                // Open StateWindow with the entered string
                std::string stateName = searchInput.getString();
                if (!stateName.empty()) {
                    StateWindow stateWindow(stateName);
                    stateWindow.run();
                }
            }
        }
    }
}



void TitleWindow::draw() {
    window.clear(sf::Color(255, 165, 0)); // Orange background

    // Calculate center positions for the text
    float centerX = window.getSize().x / 2.0f;
    float centerY = window.getSize().y / 2.0f;

    // Draw boxes around the text sections
    sf::FloatRect titleBounds = title.getGlobalBounds();
    sf::FloatRect teamInfoBounds = teamInfo.getGlobalBounds();

    // Box around the title text
    sf::RectangleShape titleBox(sf::Vector2f(titleBounds.width + 20, titleBounds.height + 20));
    titleBox.setPosition(centerX - titleBox.getSize().x / 2, titleBounds.top - 10); // Center vertically
    titleBox.setFillColor(sf::Color::White);
    titleBox.setOutlineThickness(2);
    titleBox.setOutlineColor(sf::Color::Black);
    window.draw(titleBox);

    // Box around the team info text
    sf::RectangleShape teamInfoBox(sf::Vector2f(teamInfoBounds.width + 20, teamInfoBounds.height + 20));
    teamInfoBox.setPosition(centerX - teamInfoBox.getSize().x / 2, teamInfoBounds.top - 10); // Center vertically and lower it slightly
    teamInfoBox.setFillColor(sf::Color::White);
    teamInfoBox.setOutlineThickness(2);
    teamInfoBox.setOutlineColor(sf::Color::Black);
    window.draw(teamInfoBox);

    // Title text
    title.setPosition(centerX - title.getLocalBounds().width / 2, 50); // Center horizontally
    window.draw(title);

    // Team information text
    teamInfo.setPosition(centerX - teamInfo.getLocalBounds().width / 2, centerY - teamInfo.getLocalBounds().height / 2 + 50); // Center horizontally and vertically, lower it slightly
    window.draw(teamInfo);

    // Position the image sprite between the title and team info text
    sf::FloatRect foodBounds = foodSprite.getLocalBounds();
    float imageX = centerX - foodBounds.width / 2;
    float imageY = titleBounds.top + titleBounds.height + 50; // Place the image 50 pixels below the title text
    foodSprite.setPosition(imageX, imageY);
    window.draw(foodSprite);

    window.draw(button1);
    window.draw(button2);
    window.draw(buttonText1);
    window.draw(buttonText2);

    window.draw(searchBar);
    window.draw(searchInput);
    window.draw(stateTextLabel);
    window.draw(countryTextLabel);


    static sf::Clock cursorClock;
    static bool cursorVisible = true;
    if (cursorClock.getElapsedTime().asMilliseconds() > 500) {
        cursorVisible = !cursorVisible;
        cursorClock.restart();
    }

    if (cursorVisible) {
        // Draw cursor (vertical line)
        float cursorX = searchInput.getPosition().x + searchInput.getLocalBounds().width + 5;
        float cursorY = searchInput.getPosition().y + (searchInput.getLocalBounds().height - searchInput.getCharacterSize()) / 2;
        sf::Vertex cursorLine[] = {
                sf::Vertex(sf::Vector2f(cursorX, cursorY)),
                sf::Vertex(sf::Vector2f(cursorX, cursorY + searchInput.getCharacterSize()))
        };
        window.draw(cursorLine, 2, sf::Lines);
    }


    window.display(); // Display the window contents
}

