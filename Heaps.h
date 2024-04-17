//
// Created by Caleb Jackson on 4/17/24.
//

#ifndef PROJ3_LOCAL_HEAPS_H
#define PROJ3_LOCAL_HEAPS_H

#include <iostream>
#include <vector>
#include <string>

class Max_Heap {

    // WIP

};

class Min_Heap {

    // at the moment this is the min heap which will try to store the least crimes at the root

private:

    // for this it will take processed data from the hashtable and make a count of crimes and zipcodes
    // then from there I create the tree with these two parameters and store based on count

    struct Node {
        int Count;
        int zipcode;
    };
    Node *arr;
    int capacity;
    int size;

public:

    // so we have a constructor which is going to hopefully use the number of zipcodes
    // then we have some parent, left, right functions to help traverse
    // finally, some extractions some insertion

    Min_Heap(int);
    void MinHeapify(int);
    int parent(int);
    int left(int);
    int right(int);

    // important to note that <int, int> is basically <Count, Zipcode>

    std::pair<int, int> extractMin();
    std::pair<int, int> getMin();
    void insertKey(int, int);

};


#endif //PROJ3_LOCAL_HEAPS_H
