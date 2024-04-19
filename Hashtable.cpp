//
// Created by Caleb Jackson on 4/17/24.
//

#include "Hashtable.h"

// First function is the default constructor not much to it besides setting capacity up etc
// O(1) complexity

Hashtable::Hashtable()
{
    capacity = 10;
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
    }
    if (zipcode < hashzip) {
        if (zipcode < zipmin) {
            zipmin = zipcode;
        }
    }
    if (zipcodes.size() >= loadfactor*capacity) {
        rehash(capacity*2);
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
    int hashzip = zipmin;
    std::map < int, ZipNode > nu_zipcodes;
    for (auto nodes : zipcodes){
        int key = hash(nodes.first);
        nu_zipcodes[key] = std::move(nodes.second);
    }
    zipcodes = nu_zipcodes;
}

// our function to basically flip key and the zipcode
// O (log N)

int Hashtable::getzip(int key) {
    return zipcodes[key].Zipcode;
}

// the function below gets our top 5 for the area with sorting the values stored
// O(N)

std::vector < std::pair < std::string, int > > Hashtable::getTop5Zip(int zipcode) {
    std::vector < std::pair < std::string, int > > info;
    int zip = hash(zipcode);
    for (auto items : zipcodes[zip].Crimes) {
        info.push_back(items);
    }
    std::sort(info.begin(), info.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });
    std::vector < std::pair < std::string, int > > dupe;
    for (int i = 0; i < 5; i++) {
        dupe[i] = std::move(info[i]);
    }
    return dupe;
}

std::pair<int, std::vector <std::pair <std::string, int> > > Hashtable::top5(ZipNode &s) {
    std::vector<std::pair <std::string, int> > top;
    for (auto items : s.Crimes) {
        top.push_back(items);
    }
    std::sort(top.begin(), top.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });
    std::vector<std::pair <std::string, int> > dupe;
    for (int i = 0; i < 5; i++) {
        dupe[i] = std::move(top[i]);
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
}

// this is for totaling the crimes in a given zipcode, accessed with the key, you get a zip and a crime count
// at this moment it will be used for the min/max heap

int Hashtable::NumCrimes(int key) {
    int count = 0;
    for (auto infos : zipcodes[key].Crimes) {
        count += infos.second;
    }
    return count;
}

// this function is basically gonna help the heap get made it is impractical to make the heap and fill it as the program runs
// so instead I'm electing to build the heap using the processed information stored here
// this outputs all the data needed for the heap to get working

std::vector<std::pair<int, std::map<std::string, int> > > Hashtable::Heaphelper() {
    std::vector<std::pair<int, std::map<std::string, int> > > data;
    for (auto items : zipcodes) {
        data.push_back({items.second.Zipcode, items.second.Crimes});
    }
    return data;
};
