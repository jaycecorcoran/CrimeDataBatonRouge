//
// Created by Caleb Jackson on 4/17/24.
//

#include "heap.h"

void heap::insert(int zipcode, std::map<std::string, int> crimes) {
    int count = numCrimes(crimes);
    heap::Node temp;
    temp.zipcode = zipcode;
    temp.Crimes = std::move(crimes);
    map.push({count, temp});
}

int heap::numCrimes(std::map<std::string, int> crimes) {
    int count = 0;
    for (auto obj : crimes) {
        count += obj.second;
    }
    return count;
}

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

std::pair<int, std::vector <std::pair <std::string, int> > > heap::top5(heap::Node &s) {
    std::vector<std::pair<std::string, int> > info;
    for (auto items : s.Crimes) {
        info.push_back({items.first, items.second});
    }
    std::sort(info.begin(), info.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });
    std::vector<std::pair<std::string, int> > dupe(5);
    for (int i = 0; i < 5; i++) {
        dupe[i] = info[i];
    }
    return {s.zipcode, dupe};
}

std::vector<std::pair <int, std::vector <std::pair <std::string, int> > > > heap::getTop5() {
    std::vector< std::pair <int, std::vector <std::pair < std::string, int> > > > top5vect;
    std::priority_queue< std::pair<int, Node>, std::vector<std::pair<int, Node> >, Comparison > mapt;
    mapt = map;
    for (int i = 0; i < 5; i++) {
        std::pair<int, Node> curr = mapt.top();
        mapt.pop();
        top5vect.push_back(top5(curr.second));
    }
    return top5vect;
}
