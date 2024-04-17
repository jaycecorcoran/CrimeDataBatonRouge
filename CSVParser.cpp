//
// Created by jayce on 4/16/2024.
//
#include "CSVParser.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace csv2;

CSVParser::CSVParser(const std::string& input_path, const std::string& output_path)
        : input_file_path(input_path), output_file_path(output_path) {}

bool CSVParser::parse() {
    std::ofstream out_file(output_file_path);
    if (!out_file.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return false;
    }

    Reader<delimiter<','>, quote_character<'"'>, first_row_is_header<true>> csv;
    if (csv.mmap(input_file_path)) {
        auto header = csv.header();
        std::vector<std::string> header_values;
        for (const auto &cell : header) {
            header_values.emplace_back(cell.read_view());
        }

        // Find column indices based on header values
        int date_col = -1, zip_col = -1, crime_cat_col = -1;
        for (size_t i = 0; i < header_values.size(); ++i) {
            if (header_values[i] == "date") date_col = i;
            else if (header_values[i] == "zip_code") zip_col = i;
            else if (header_values[i] == "crime_statute_category") crime_cat_col = i;
        }

        // Check if column indices were found
        if (date_col == -1 || zip_col == -1 || crime_cat_col == -1) {
            std::cerr << "Could not find one or more required columns." << std::endl;
            return false;
        }

        // Write header
        out_file << "Date,Zip Code,Crime Statute Category\n";

        for (const auto &row : csv) {
            std::vector<std::string> values;
            for (const auto &cell : row) {
                values.emplace_back(cell.read_view());
            }
            // Write the required values if the row has enough cells
            if (values.size() > std::max({date_col, zip_col, crime_cat_col})) {
                out_file << values[date_col] << "," << values[zip_col] << "," << values[crime_cat_col] << "\n";
            }
        }
    } else {
        std::cerr << "Failed to open the input CSV file." << std::endl;
        return false;
    }

    out_file.close();
    return true;
