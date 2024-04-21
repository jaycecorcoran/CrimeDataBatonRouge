//
// Created by thoma on 4/18/2024.
//

#include "CityWindow.h"

CityWindow::CityWindow(const std::string& structureType, class heap heap, Hashtable hash) : window(sf::VideoMode(1200, 900), "City Data Visualization"), dataStructureType(structureType) {
    this->heap = heap;
    this->hashtable = hash;
    loadFont();
    loadBackgroundImage();
    setupTitleText();
    setupCrimeRateText();
    setupCrimeRateRows();
}

void CityWindow::run() {
    while (window.isOpen()) {
        // the request focus will bring the window forward and select it
        window.requestFocus();
        window.setActive(true);
        handleEvents();
        draw();
    }
}

void CityWindow::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            // the set active being false should help keep the windows in focus
            window.setActive(false);
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
    std::vector<std::string> crime;
    sf::Text time;
    time.setFont(font);
    if (dataStructureType == "heap") {
        auto start = high_resolution_clock::now();
        crime = heap.getTop5Num();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        time.setString("Time using a Heap: " +std::to_string(duration.count()) + " microseconds");
    }
    else {
        auto start = high_resolution_clock::now();
        crime = hashtable.getTop5Num();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        time.setString("Time using a Hashtable: " + std::to_string(duration.count()) + " microseconds");
        auto info = hashtable.getzipinfo(70805);
    }

    time.setCharacterSize(20);
    time.setFillColor(sf::Color::Black);
    time.setPosition(400.f, 600.f + 5 * 35.f);

    // Sample crime rate rows
    const float startY = 600.f;
    const float lineHeight = 35.f;
    for (size_t i = 0; i < crime.size(); ++i) {
        sf::Text row;
        row.setFont(font);
        row.setString(crime[i]);
        row.setCharacterSize(20);
        row.setFillColor(sf::Color::Black);
        row.setPosition(300.f, startY + i * lineHeight);
        crimeRateRows.push_back(row);
    }
    crimeRateRows.push_back(time);
}
