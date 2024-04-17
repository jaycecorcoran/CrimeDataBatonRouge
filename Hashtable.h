//
// Created by Caleb Jackson on 4/17/24.
//

#include <iostream>
#include <string>
#include <map>
#include <vector>

#ifndef PROJ3_LOCAL_HASHTABLE_H
#define PROJ3_LOCAL_HASHTABLE_H

// these commments are for my groupmates as well as the graders I'll begin by talking about the variables!

class Hashtable {

private:

    // First off I want to make a Node to store 2 important variables (basically 3) but yeah
    // The Node has a zipcode attached to it, since the map will be using a hash function based on the zipcode,
    // Then the Node has a map for crimes, this will be used to count up unique offenses and then tally them up

    struct ZipNode{
        int Zipcode;
        std::map<std::string, int> Crimes;
    };

    // now, I have a hashzip which will be seen later, but basically it is going to be the zipcode I'm going to use
    // for the hash function, once again more on that later
    // next I want to make a load factor so the table can be rehashed rather often since the zipcode can change often
    // now, for the actual container, I elected to use a map where I can store the keys ( hash(zipcode) ) and access
    // the data which is crimes and count etc etc, the capacity is just a placeholder tbh, and zipmin is something
    // that you will see when taking a look at our rehash function!

    int hashzip;
    const double loadfactor = 0.70;
    std::map < int, ZipNode> zipcodes;
    int capacity;
    int zipmin;

public:

    // for all of these functions, they will assume that you will be calling them with the key instead of the zip
    // if you want to access something using a zipcode you must convert it using hash to get the key
    // I don't like to write the actual variable names here as they change but I will separate them by the assumptions

    // these are the unique ones that actually make it a hashtable! first the constructor and then the hash function

    Hashtable();
    int hash(int);

    // next I have some of the important things such as insertion, rehashing, and an accessor for the zipcode huh??
    // as you'll see basically my hash function takes a zipcode and turns it to a key, this is a way of turning it back

    void insert(int, std::string);
    void rehash(int);
    int getzip(int);

    // next I have our grand assortment of accessor functions, getting info for a zipcode, getting the maxes, getting mins
    // if you can commit it often or once, it'll come back in this data set

    // this is the only accessor function atm that will use the zipcode to get information about an area

    std::vector<std::pair<std::string, int> > getzipinfo(int);

    // the rest of the accessors use the key to get the information

    std::pair<std::string, int> getMax(int);
    std::vector<std::pair<int, std::pair<std::string, int> > > getallMax();
    std::pair<std::string, int> getMin(int);
    std::vector<std::pair<int, std::pair<std::string, int> > > getallMin();
    std::pair<int, int> getMaxByCrime(std::string);
    std::pair<int, int> NumCrimes(int);
    std::vector<std::pair<int, int> > NumCrimesAll();
    int getSize();

};


#endif //PROJ3_LOCAL_HASHTABLE_H
