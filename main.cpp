//FoodWasters project
#include <SFML/graphics.hpp>
#include <iostream>
#include "Window.h"
#include "StateWindow.h"
#include "CSVParser.h"
using namespace std;

int main() {
// Replace with the path to your CSV file
    std::string input_path = "Baton_Rouge_Police_Crime_Incidents.csv";

    // Create a CSVParser instance
    CSVParser parser(input_path);

    // Vector to hold the pairs of crime category and zip code
    std::vector<std::pair<std::string, int>> data;

    // Parse the CSV file
    if (parser.parse(data)) {
        // If parsing is successful, print out the pairs
        for (const auto& pair : data) {
            std::cout << "Crime Category: " << pair.first << " - Zip Code: " << pair.second << std::endl;
        }
    } else {
        std::cerr << "Failed to parse the CSV file." << std::endl;
        return 1;
    }
    /*
    //SFML test from minesweeper project
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            window.clear();
            window.draw(shape);
            window.display();
        }
    }
    return 0;
     */

    TitleWindow titleWindow;
    titleWindow.run();



    return 0;
}

