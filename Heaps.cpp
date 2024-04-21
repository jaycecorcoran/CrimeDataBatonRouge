//
// Created by Caleb Jackson on 4/17/24.
//

#include "Heaps.h"

// for insertion into the heap we have a time complexity of O (log N + V) where V is the number of instances in the crimes
// and N is the size of the queue this function relies on that to take count (otherwise it would be extremely quick)
// simply put I am counting up the number of crimes to push it into the queue

void heap::insert(int zipcode, std::map<std::string, int> crimes) {
    int count = numCrimes(crimes);
    heap::Node temp;
    temp.zipcode = zipcode;
    temp.Crimes = std::move(crimes);
    map.push({count, temp});
}

// and for num crimes as seen before with the explanation the time complexity is O(V) for the number of unique instances

int heap::numCrimes(std::map<std::string, int> crimes) {
    int count = 0;
    for (auto obj : crimes) {
        count += obj.second;
    }
    return count;
}

// the function below is the work of many different functions I wrote, then they morphed by the time the final product
// came around, as you can see the only main thing to cause complexity is copying over the queue to another object
// with this operation it takes a good bit of complexity and for this container I would assume it is O (log V + O(5*3) )
// assuming we have a constant time complexity on copying V number of Nodes, while this could be implemented by popping
// the original queue I want to keep the heap intact

std::vector<std::string> heap::getTop5Num() {
    std::vector<std::string> top5;
    std::priority_queue< std::pair<int, Node>, std::vector<std::pair<int, Node> >, Comparison > mapt;
    mapt = map;
    for (int i = 0; i < 5; i++) {
        std::pair<int, Node> curr = mapt.top();
        mapt.pop();
        std::string temp = std::to_string(curr.second.zipcode) + " with " + std::to_string(curr.first) + " crimes [";
        int count = 0;
        std::map<int, std::string, std::greater<int> > te;
        for (auto item : curr.second.Crimes) {
            te[item.second] = item.first;
        }
        for (auto item : te) {
            if (count < 2) {
                temp += item.second + ", ";
                count++;
            }
            else {
                temp += item.second;
                break;
            }
        }
        temp += "]";
        top5.push_back(temp);
    }
    return top5;
}

// this is the beginning of the graveyard, but we have some cool stuff going on in here, for instance this one below
// when testing the times for the random access on the heap is terrible compared to the hash table as we have a O(1) vs
// O(n) and it can be seen in the results. The thought process behind this function is to use a BFS to create random access
// something not typically used, but it was for the prototypes of the project.

std::vector <std::pair <std::string, int> > heap::getTop5Zip (int zipcode) {
    std::vector<std::pair<std::string, int> > info;
    std::priority_queue< std::pair<int, Node>, std::vector<std::pair<int, Node> >, Comparison > mapt;
    mapt = map;
    Node temp;
    while (!mapt.empty()) {
        std::pair<int, Node> curr = mapt.top();
        mapt.pop();
        if (curr.second.zipcode == zipcode) {
            temp.zipcode = curr.second.zipcode;
            temp.Crimes = curr.second.Crimes;
            break;
        }
    }
    for (auto items : temp.Crimes) {
        info.push_back({items.first, items.second});
    }
    std::sort(info.begin(), info.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });
    std::vector<std::pair<std::string, int> > dupe(5);
    for (int i = 0; i < 5; i++) {
        dupe[i] = info[i];
    }
    return dupe;
}