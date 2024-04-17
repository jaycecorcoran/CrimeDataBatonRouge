//
// Created by jayce on 4/16/2024.
//

#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <string>
#include "csv2/include/csv2/reader.hpp"

class CSVParser {
public:
    CSVParser(const std::string& input_path, const std::string& output_path);
    bool parse();

private:
    std::string input_file_path;
    std::string output_file_path;
};

#endif // CSVPARSER_H
