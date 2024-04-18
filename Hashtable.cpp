 //
// Created by Caleb Jackson on 4/17/24.
//

#include "Hashtable.h"

// First function is the default constructor not much to it besides setting capacity up etc

Hashtable::Hashtable()
{
    capacity = 10;
    hashzip = 0;
    zipmin = 99999;
}

// this is what I use hashzip for, basically if we insert I know the hashzip will be different before calling,
// but I try to keep this to the smallest zipcode so we can avoid having huge keys.

int Hashtable::hash(int zipcode) {
    return zipcode % hashzip;
}

// now insertion, all we take is the zipcode and crime and work from there, pretty standard stuff

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

void Hashtable::rehash(int new_capacity)
{
    capacity = new_capacity;
    int hashzip = zipmin;
    std::map < int, ZipNode > nu_zipcodes;
    for (auto nodes : zipcodes){
        int key = hash(nodes.first);
        nu_zipcodes[key] = nodes.second;
    }
    zipcodes = nu_zipcodes;
}

// our function to basically flip key and the zipcode

int Hashtable::getzip(int key) {
    return zipcodes[key].Zipcode;
}

// a function that will give us a vector of all crime info for a given zipcode

std::vector<std::pair<std::string, int> > Hashtable::getzipinfo(int zipcode) {
    std::vector<std::pair<std::string, int> > info;
    int zip = hash(zipcode);
    for (auto infos : zipcodes[zip].Crimes) {
        info.push_back(infos);
    }
    return info;
}

// once again rather simple function that is basically a helper to get the max crime in a given key

std::pair<std::string, int> Hashtable::getMax(int key) {
    std::pair<std::string, int> max;
    std::string Crime;
    for (auto infos : zipcodes[key].Crimes) {
        if (infos.second > max.second) {
            max = infos;
        }
    }
    return max;
}

// this is the big function to list all the max crimes in each zipcode, it has a vector of pair of a pair, 3 variables
// and they go as follows, <int, <string, int> > the first int is for the zipcode, the string is the crime in that zip
// the last integer is for the number of crimes committed

std::vector<std::pair<int, std::pair<std::string, int> > > Hashtable::getallMax() {
    std::vector<std::pair<int, std::pair<std::string, int> > > maxes;
    for (auto infos : zipcodes) {
        std::pair<std::string, int> maxzip = getMax(infos.first);
        maxes.push_back({infos.second.Zipcode, (maxzip)});
    }
    return maxes;
}

// basically inverse of the max function

std::pair<std::string, int> Hashtable::getMin(int key) {
    std::pair<std::string, int> min;
    std::string Crime;
    for (auto infos : zipcodes[key].Crimes) {
        if (infos.second < min.second) {
            min = infos;
        }
        if (min.second == 0 && min.first == "") {
            min = infos;
        }
    }
    return min;
}

std::vector<std::pair<int, std::pair<std::string, int> > > Hashtable::getallMin() {
    std::vector<std::pair<int, std::pair<std::string, int> > > mins;
    for (auto infos : zipcodes) {
        std::pair<std::string, int> maxzip = getMin(infos.first);
        mins.push_back({infos.second.Zipcode, (maxzip)});
    }
    return mins;
}

// now this is for looking into the max of all the zipcodes for a given crime, for instance homicide, you would put,
// then you will get the zipcode and the count representing the max

std::pair<int, int> Hashtable::getMaxByCrime(std::string crime) {
    std::pair<int, int> max;
    for (auto infos : zipcodes) {
        if (infos.second.Crimes[crime] > max.second) {
            max.first = infos.second.Zipcode;
            max.second = infos.second.Crimes[crime];
        }
    }
    return max;
}

// this is for totaling the crimes in a given zipcode, accessed with the key, you get a zip and a crime count
// at this moment it will be used for the min/max heap

std::pair<int, int> Hashtable::NumCrimes(int key) {
    int count = 0;
    int zip = getzip(key);
    for (auto infos : zipcodes[key].Crimes) {
        count += infos.second;
    }
    return std::make_pair(zip, count);
}

// this is a vector function to give the number of crimes in all zipcodes in the data, theyll come back as a pair

std::vector<std::pair<int, int> > Hashtable::NumCrimesAll() {
    std::vector<std::pair<int, int> > all;
    for (auto infos : zipcodes) {
        all.push_back(NumCrimes(infos.first));
    }
    return all;
}

int Hashtable::getSize() {
    return (zipcodes.size());
}