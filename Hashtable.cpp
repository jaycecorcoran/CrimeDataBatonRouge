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
// O (log N * log V) complexity without rehashing O(N * V + log V * log N) with rehash N being the number of objects
// in the table of course V being the number of objects in the map items of each object
// for example we need to make sure the hashing variables are good so I run some comparison operators

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
        rehash(capacity+2);
    }
    int key = hash(zipcode);
    zipcodes[key].Zipcode = zipcode;
    zipcodes[key].Crimes[crime] += 1;
}

// rehash is a little unique as I use my zipmin to create the new hash function as you can see, but just lots of moving
// O(N * V) complexity as I use an overloaded operator to copy over the map but for N objects of the zipcodes map we
// have to move over V objects of the zipnode map;

void Hashtable::rehash(int new_capacity)
{
    capacity = new_capacity;
    std::map < int, ZipNode > nu_zipcodes;
    for (auto nodes : zipcodes){
        int key = nodes.second.Zipcode % zipmin;
        nu_zipcodes[key] = nodes.second;
    }
    zipcodes = std::move(nu_zipcodes);
    hashzip = zipmin;
}

// this is the part that stated previously has O(V) complexity as we copy all objects in the sub maps, so for V objects
// we need to iterate through them

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
// so for the info we can just push back the values for the crimes simply enough O(V) and then with sort we have
// a bit of an issue as we get a complexity of O(V * log V) as stated on cpp reference meaning our final complexity
// is O(V*logV) as we need to do this sorting algorithm

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
// this function has a complexity of O(N) where we are just outputting all the data in the table simply enough

std::vector<std::pair<int, std::map<std::string, int> > > Hashtable::Heaphelper() {
    std::vector<std::pair<int, std::map<std::string, int> > > data;
    for (auto items : zipcodes) {
        data.push_back({items.second.Zipcode, items.second.Crimes});
    }
    return data;
};

// below is the function that will give us the final product for the top 5 areas in terms of crime, the beginning of it
// takes our map and iterates through the objects in it and we use num crimes to tally up the total crimes of the area
// so as you can see we call NumCrimes for all the objects in the array meaning we have a complexity so far of
// O(V * N) since we need to tally up all the objects crimes, then we have the sorting algorithm once again
// and the sorting will give us a complexity of O(N * logN) since we are sorting by the number of objects in the array
// giving us a complexity of O(V*N + N*logN) since there are varying quantities, it depends on the situation which is
// greater cost while I do copy over the map with O(N) complexity it doesn't compare to these two in time

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
                temp += item.second + ", ";
                count++;
            }
            else if (count < 2) {

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