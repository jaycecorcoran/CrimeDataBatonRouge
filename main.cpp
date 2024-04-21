//FoodWasters project
#include <SFML/graphics.hpp>
#include <iostream>
#include "Window.h"
#include "ZipWindow.h"
#include "CSVParser.h"
#include "Heaps.h"
#include "Hashtable.h"
using namespace std;

int main() {
    /*Hashtable hashtable;
    heap heap;
// Replace with the path to your CSV file
    std::string input_path = "crimeDataSet.csv";
//
//    // Create a CSVParser instance
    CSVParser parser(input_path);
//
//    // Vector to hold the pairs of crime category and zip code
    std::vector<std::pair<int, std::string>> data;
//
//    // Parse the CSV file
    if (parser.parse(data)) {
//        // If parsing is successful, print out the pairs
        for (const auto &pair: data) {
            hashtable.insert(pair.first, pair.second);
            //std::cout << "Zip Code: " << pair.first << " - Statute Category: " << pair.second << std::endl;
        }
//        }
//    } else {
//        std::cerr << "Failed to parse the CSV file." << std::endl;
//        return 1;
//    }
        std::vector<std::pair<int, std::map<std::string, int> > > help = hashtable.Heaphelper();
        for (auto item: help) {
            heap.insert(item.first, item.second);
        }*/
        /*//SFML test from minesweeper project
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