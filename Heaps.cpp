//
// Created by Caleb Jackson on 4/17/24.
//

#include "Heaps.h"

// unfortunately, I chose to use a model with two values so it is a bit annoying to deal with

Min_Heap::Min_Heap(int cap)
{
    size = 0;
    capacity = cap;
    arr = new Node[cap];
}

int Min_Heap::parent(int index) {
    return (index-1)/2;
}

int Min_Heap::left(int index) {
    return 2*index + 1;
}

int Min_Heap::right(int index) {
    return 2*index + 2;
}

// so insert key is our first look, you get to see how std::swap failed me and the use of a ton of different variables

void Min_Heap::insertKey(int count, int zip) {
    if (size == capacity)
    {
        return;
    }
    size++;
    int i = size-1;
    arr[i] = {count,zip};
    while (i != 0 && arr[parent(i)].Count > arr[i].Count){
        std::pair<int, int> tempparent = {arr[parent(i)].Count, arr[parent(i)].zipcode};
        std::pair<int, int> tempindex = {arr[i].Count, arr[i].zipcode};
        arr[i].Count = tempparent.first;
        arr[i].zipcode = tempparent.second;
        arr[parent(i)].Count = tempindex.first;
        arr[parent(i)].zipcode = tempindex.second;
        i = parent(i);
    }
}

std::pair<int,int> Min_Heap::extractMin()
{
    if (size <= 0) {
        return {0,0};
    }
    if (size == 1) {
        size--;
        return {arr[0].Count, arr[0].zipcode};
    }
    std::pair<int, int> root = {arr[0].Count, arr[0].zipcode};
    arr[0] = arr[size-1];
    size--;
    MinHeapify(0);
}

void Min_Heap::MinHeapify(int index) {
    int l = left(index);
    int r = right(index);
    int min = index;
    if (l < size && arr[l].Count < arr[index].Count) {
        min = l;
    }
    if (l < size && arr[r].Count < arr[min].Count) {
        min = r;
    }
    if (min != index){
        int tempc1 = arr[index].Count;
        int tempc2 = arr[min].Count;
        arr[index].Count = tempc2;
        arr[min].Count = tempc1;
        tempc1 = arr[index].zipcode;
        tempc2 = arr[min].zipcode;
        arr[index].zipcode = tempc2;
        arr[min].zipcode = tempc1;
        MinHeapify(min);
    }
}

std::pair<int, int> Min_Heap::getMin()
{
    return {arr[0].Count, arr[0].zipcode};
}

