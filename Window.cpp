//
// Created by thoma on 4/15/2024.
//
#include "Window.h"

Window::~Window() {}



TitleWindow::TitleWindow() : window(sf::VideoMode(1200, 900), "Crime Data Visualization") {
    if (!font.loadFromFile("Lato-Black.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    if (!criminalTexture.loadFromFile("slasher.png")) {
        std::cerr << "Failed to load food image" << std::endl;
    }
    if (!buttonTexture.loadFromFile("tile_hidden.png")) {
        std::cerr << "Failed to load button texture";
    }

    // back-end here and basically we are going to do all of the mathematics and calculations within window
    // so this will be a frankenstein of our work, it will call the parser, the hashtables, and the heap

    std::string input_path = "crimeDataSet.csv";
    CSVParser parser(input_path);
    std::vector<std::pair<int, std::string>> data;
    if (parser.parse(data)) {
        for (const auto &pair: data) {
            hashtable.insert(pair.first, pair.second);
        }
    }
    std::vector<std::pair<int, std::map<std::string, int> > > help = hashtable.Heaphelper();
    for (auto item: help) {
        heap.insert(item.first, item.second);
    }

    validZipCodes = {"70820", "70802", "70805", "70815", "70807", "70816", "70809", "70806", "70726", "70811", "70808",
                     "70801", "70819", "70769", "70770", "70814", "70810", "70812", "70825", "70836", "70791", "70813",
                     "70817", "70782", "70185", "70823", "79816", "70502", "70783", "30083", "70803", "70818", "70053",
                     "70785", "70422", "70508", "71101", "70767", "70062", "70898", "77099", "76018", "70503", "70804",
                     "70739", "70722", "70714"};

    displayErrorMessage = false;

    // Set up the picture sprite
    criminalSprite.setTexture(criminalTexture);

    title.setFont(font);
    title.setString("Visualization of Baton Rouge Crime Data");
    title.setCharacterSize(36);
    title.setFillColor(sf::Color::Black);

    // Initialize team information text
    teamInfo.setFont(font);
    teamInfo.setString("                  THE HASH SLINGING SLASHERS\nThomas Chappell, Jayce Corcoran, Caleb Jackson");
    teamInfo.setCharacterSize(24);
    teamInfo.setFillColor(sf::Color::Black);

    // Set up button rectangles
    button1.setSize(sf::Vector2f(200, 60));
    button1.setTexture(&buttonTexture);
    button1.setPosition(300, 700);

    button2.setSize(sf::Vector2f(200, 60));
    button2.setTexture(&buttonTexture);
    button2.setPosition(700, 700);

    // Set up button text
    buttonText1.setFont(font);
    buttonText1.setString("Heap");
    buttonText1.setCharacterSize(24);
    buttonText1.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds1 = buttonText1.getLocalBounds();
    buttonText1.setPosition(button1.getPosition().x + (button1.getSize().x - textBounds1.width) / 2, button1.getPosition().y + (button1.getSize().y - textBounds1.height) / 2);

    buttonText2.setFont(font);
    buttonText2.setString("Hash Table");
    buttonText2.setCharacterSize(24);
    buttonText2.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds2 = buttonText2.getLocalBounds();
    buttonText2.setPosition(button2.getPosition().x + (button2.getSize().x - textBounds2.width) / 2, button2.getPosition().y + (button2.getSize().y - textBounds2.height) / 2);

    searchBar.setSize(sf::Vector2f(600, 40));
    searchBar.setFillColor(sf::Color::White);
    searchBar.setOutlineThickness(2);
    searchBar.setOutlineColor(sf::Color::Black);
    searchBar.setPosition(300, 580);

    // Search input text setup
    searchInput.setFont(font);
    searchInput.setString("Please enter a valid zip code (Listed in README file)");
    searchInput.setCharacterSize(20);
    searchInput.setFillColor(sf::Color(105, 105, 105));
    searchInput.setPosition(305, 590);

    // Text labels setup
    zipTextLabel.setFont(font);
    zipTextLabel.setString("To view data by zip code:");
    zipTextLabel.setCharacterSize(20);
    zipTextLabel.setFillColor(sf::Color::Black);
    sf::FloatRect stateTextBounds = zipTextLabel.getLocalBounds();
    zipTextLabel.setPosition((window.getSize().x - stateTextBounds.width) / 2, 550);

    cityTextLabel.setFont(font);
    cityTextLabel.setString("To view data by city:");
    cityTextLabel.setCharacterSize(20);
    cityTextLabel.setFillColor(sf::Color::Black);
    sf::FloatRect countryTextBounds = cityTextLabel.getLocalBounds();
    cityTextLabel.setPosition((window.getSize().x - countryTextBounds.width) / 2, 650);

    errorMessage.setFont(font);
    errorMessage.setString("Error: Please input a valid zip code");
    errorMessage.setCharacterSize(20);
    errorMessage.setFillColor(sf::Color::Red);
    errorMessage.setPosition((window.getSize().x - errorMessage.getLocalBounds().width) / 2, 800);
}

void TitleWindow::run() {
    while (window.isOpen()) {
        window.setActive();
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
            // Clear the search input when the search bar is clicked
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::FloatRect searchBarBounds = searchBar.getGlobalBounds();
            if (searchBarBounds.contains(mousePos.x, mousePos.y)) {
                searchInput.setString("");
                // Reset the error message flag
                displayErrorMessage = false;
            }
            sf::FloatRect button1Bounds = button1.getGlobalBounds();
            if (button1Bounds.contains(mousePos.x, mousePos.y)) {
                // Create a new CityWindow instance and run it
                CityWindow cityWindow("heap", heap, hashtable);
                cityWindow.run();
            }
            // Check if the mouse is clicked within button2
            sf::FloatRect button2Bounds = button2.getGlobalBounds();
            if (button2Bounds.contains(mousePos.x, mousePos.y)) {
                // Create a new CityWindow instance and run it
                CityWindow cityWindow("hashtable", heap, hashtable);
                cityWindow.run();
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
                // Check if the entered zip code is valid
                std::string zipCode = searchInput.getString();
                if (isValidZipCode(zipCode)) {
                    // Open ZipWindow with the entered string
                    int zip = stoi(zipCode);
                    auto crimes = hashtable.getTop5Zip(zip);
                    std::cout << zipCode << "l" << std::endl;
                    ZipWindow zipWindow(zipCode, crimes);
                    zipWindow.run();
                    displayErrorMessage = false;
                } else {
                    // Display error if not a valid zip code
                    displayErrorMessage = true;
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
    sf::FloatRect foodBounds = criminalSprite.getLocalBounds();
    float imageX = centerX - foodBounds.width / 2;
    float imageY = titleBounds.top + titleBounds.height + 25; // Place the image 50 pixels below the title text
    criminalSprite.setPosition(imageX + 45, imageY - 30);
    window.draw(criminalSprite);

    window.draw(button1);
    window.draw(button2);
    window.draw(buttonText1);
    window.draw(buttonText2);

    window.draw(searchBar);
    window.draw(searchInput);
    window.draw(zipTextLabel);
    window.draw(cityTextLabel);

    if (displayErrorMessage) {
        window.draw(errorMessage);
    }


    window.display(); // Display the window contents
}

bool TitleWindow::isValidZipCode(const std::string& zipCode) const {
    return validZipCodes.count(zipCode) > 0;
}
