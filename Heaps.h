//
// Created by Caleb Jackson on 4/17/24.
//

#ifndef PROJ3_HEAPS_H
#define PROJ3_HEAPS_H

#include <iostream>
#include <queue>
#include <map>
#include <vector>

class heap {

private:

    // the first part of the project is using a node similar to the hashtable to store the points

    struct Node {
        int zipcode;
        std::map<std::string, int> Crimes;
    };
    // a comparison operator I need to actually make the priority queue work since I have weird types!

    struct Comparison {
        constexpr bool operator() ( std::pair<int, Node> const& a, std::pair<int, Node> const& b) const noexcept
        {
            return a.first < b.first;
        }
    };

    // now for the actual max heap it'll work based on the count size and have a node attached

    std::priority_queue< std::pair<int, Node>, std::vector<std::pair<int, Node> >, Comparison > map;

public:

    // so this num crimes function is to basically tally up the items in the map

    int numCrimes(std::map<std::string, int>);

    // and our insert is for inserting items into the max heap

    void insert(int, std::map<std::string, int>);

    // now this all is for getting our data and we are going to access it in two ways, listing the top 5 in all
    // and listing the top 5 in one given zip

    std::vector <std::pair <std::string, int> > getTop5Zip(int);
    std::pair<int, std::vector <std::pair <std::string, int> > > top5(heap::Node &s);
    std::vector<std::pair <int, std::vector <std::pair <std::string, int> > > > getTop5();

};

#endif //PROJ3_HEAPS_H
