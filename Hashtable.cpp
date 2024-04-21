//
// Created by Caleb Jackson on 4/17/24.
//

#include "Hashtable.h"

// First function is the default constructor not much to it besides setting capacity up etc
// O(1) complexity

Hashtable::Hashtable()
{
    capacity = 2;
    hashzip = 0;
    zipmin = 99999;
}

// this is what I use hashzip for, basically if we insert I know the hashzip will be different before calling,
// but I try to keep this to the smallest zipcode so we can avoid having huge keys.
// O(1) complexity

int Hashtable::hash(int zipcode) {
    return zipcode % hashzip;
}

// now insertion, all we take is the zipcode and crime and work from there, pretty standard stuff
// O (log N) complexity without rehashing O(n) with rehash

void Hashtable::insert(int zipcode, std::string crime) {
    if (hashzip == 0)
    {
        hashzip = zipcode;
        zipmin = zipcode;
    }
    if (zipcode < zipmin) {
        zipmin = zipcode;
    }
    if (zipcodes.size() + 1 >= loadfactor*capacity) {
        //std::cout << "rehashing" << "\n";
        rehash(capacity+2);
    }
    int key = hash(zipcode);
    zipcodes[key].Zipcode = zipcode;
    zipcodes[key].Crimes[crime] += 1;
}

// rehash is a little unique as I use my zipmin to create the new hash function as you can see, but just lots of moving
// O(n) complexity

void Hashtable::rehash(int new_capacity)
{
    capacity = new_capacity;
    //std::cout << hashzip << " " << zipmin << "\n";
    std::map < int, ZipNode > nu_zipcodes;
    for (auto nodes : zipcodes){
        int key = nodes.second.Zipcode % zipmin;
        nu_zipcodes[key] = nodes.second;
    }
    zipcodes = std::move(nu_zipcodes);
    hashzip = zipmin;
}

Hashtable::ZipNode Hashtable::ZipNode::operator=(Hashtable::ZipNode s) {
    this->Zipcode = s.Zipcode;
    int i = 0;
    for (auto items : s.Crimes)
    {
        this->Crimes[items.first] = items.second;
        i++;
    }
    return *this;
}

// the function below gets our top 5 for the area with sorting the values stored it uses a rather simple concept
// there is a bit of difficulty as with many of these operations when it comes to the sorting

std::vector < std::pair < std::string, int > > Hashtable::getTop5Zip(int zipcode) {
    std::vector < std::pair < std::string, int > > info;
    int zip = hash(zipcode);
    for (auto items : zipcodes[zip].Crimes) {
        info.push_back(items);
    }
    std::sort(info.begin(), info.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });
    std::vector < std::pair < std::string, int > > dupe(5);
    for (int i = 0; i < 5; i++) {
        dupe[i] = info[i];
    }
    return dupe;
}

// this is for totaling the crimes in a given zipcode, accessed with the key, you get a zip and a crime count
// at this moment it will be used for the min/max heap
// in the final implementation it is very useful for our top 5, with a time complexity of O (V) the number of instances
// in a given zipcode

int Hashtable::NumCrimes(int key) {
    int count = 0;
    for (auto infos : zipcodes[key].Crimes) {
        count += infos.second;
    }
    return count;
}

// this function is basically gonna help the heap get made it is impractical to make the heap and fill it as the program runs
// so instead I'm electing to build the heap using the processed information stored here

std::vector<std::pair<int, std::map<std::string, int> > > Hashtable::Heaphelper() {
    std::vector<std::pair<int, std::map<std::string, int> > > data;
    for (auto items : zipcodes) {
        data.push_back({items.second.Zipcode, items.second.Crimes});
    }
    return data;
};

// below is the function that will give us the final product for the top 5 areas in terms of crime, the beginning of it
// takes our map and iterates through the objects in it and we use num crimes to tally up the total crimes of the area
//

std::vector<std::string> Hashtable::getTop5Num() {
    std::vector<std::string> top5;
    std::vector<std::pair < int, ZipNode > > holder;
    for (auto items : zipcodes) {
        holder.push_back({NumCrimes(items.first), items.second});
    }
    std::sort(holder.begin(), holder.end(), [](auto &a, auto &b) {
        return a.first > b.first;
    });
    for (int i = 0; i < 5; i++) {
        int count = 0;
        std::string temp = std::to_string(holder[i].second.Zipcode) + " with " + std::to_string(holder[i].first) + " crimes [";
        auto tem = holder[i].second.Crimes;
        std::map<int, std::string, std::greater<int> > te;
        for (auto item : tem) {
            te[item.second] = item.first;
        }
        for (auto item : te) {
            if (count < 2 && item.second != "NOT USED") {
                std::cout << item.second << std::endl;
                temp += item.second + ", ";
                count++;
            }
            else if (count < 2)
            {

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

// Below is the memory of the previous functions that had a use, but now go unused

// our function to basically flip key and the zipcode
// O (log N)

std::vector<std::pair<std::string, int> > Hashtable::getzipinfo(int zipcode) {
    int zip = hash(zipcode);
    std::vector<std::pair<std::string, int>> he;
    for (auto items : zipcodes[zip].Crimes){
        std::cout << items.first << " " << items.second << "\n";
    }
    return he;
}

int Hashtable::getzip(int key) {
    return zipcodes[key].Zipcode;
}

std::pair<int, std::vector <std::pair <std::string, int> > > Hashtable::top5(ZipNode &s) {
    std::vector<std::pair <std::string, int> > top;
    for (auto items : s.Crimes) {
        top.push_back(items);
    }
    std::sort(top.begin(), top.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });
    std::vector<std::pair <std::string, int> > dupe(5);
    for (int i = 0; i < 5; i++) {
        dupe[i] = top[i];
    }
    return {s.Zipcode, dupe};
}

std::vector<std::pair <int, std::vector <std::pair <std::string, int> > > > Hashtable::getTop5() {
    std::vector<std::pair <int, std::vector <std::pair <std::string, int> > > > top;
    std::vector<std::pair < int, ZipNode > > holder;
    for (auto items : zipcodes) {
        holder.push_back({NumCrimes(items.first), items.second});
    }
    std::sort(holder.begin(), holder.end(), [](auto &a, auto &b) {
        return a.first > b.first;
    });
    for (int i = 0; i < 5; i++) {
        top.push_back(top5(holder[i].second));
    }
    return top;
}
