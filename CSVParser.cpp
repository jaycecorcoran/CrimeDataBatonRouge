//
// Created by jayce on 4/16/2024.
//
#include "CSVParser.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <utility> // For std::pair
#include <sstream> // For std::stringstream
using namespace csv2;

CSVParser::CSVParser(const std::string& input_path)
        : input_file_path(input_path) {}

bool CSVParser::parse(std::vector<std::pair<int, std::string>>& data) {
    Reader<delimiter<','>, quote_character<'"'>, first_row_is_header<true>> csv;
    if (csv.mmap(input_file_path)) {
        auto header = csv.header();
        std::vector<std::string> header_values;
        for (const auto &cell : header) {
            header_values.emplace_back(cell.read_view());
        }

        // Find column indices based on header values
        int zip_col = 0, crime_cat_col = 1;
        for (size_t i = 0; i < header_values.size(); ++i) {
            //std::cout << i << std::endl;
            //std::cout << header_values.size() << std::endl;
            if (header_values[i] == "ZIP CODE") zip_col = i;
            else if (header_values[i] == "STATUTE CATEGORY") crime_cat_col = i;
        }

        // Check if column indices were found
        if (zip_col == -1 || crime_cat_col == -1) {
            std::cerr << "Could not find one or more required columns." << std::endl;
            return false;
        }

        for (const auto &row : csv) {
            std::vector<std::string> values;
            for (const auto &cell : row) {
                values.emplace_back(cell.read_view());
            }
            // Create the pair if the row has enough cells
            if (values.size() > std::max(zip_col, crime_cat_col)) {
                try {
                    int zip_code = std::stoi(values[zip_col]);
                    data.emplace_back(zip_code, values[crime_cat_col]);
                } catch (const std::invalid_argument& ia) {
                    // Skip the row if zip code is not an integer
                    continue;
                }
            }
        }
        return true;
    } else {
        std::cerr << "Failed to open the input CSV file." << std::endl;
        return false;
    }
}