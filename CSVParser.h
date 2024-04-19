//
// Created by jayce on 4/16/2024.
//
#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <string>
#include <vector>
//#include "csv2/include/csv2/reader.hpp"
#include "csv2/single_include/csv2/csv2.hpp"

class CSVParser {
public:
    CSVParser(const std::string& input_path);
    bool parse(std::vector<std::pair<int, std::string>>& data);

private:
    std::string input_file_path;
};

#endif // CSVPARSER_H