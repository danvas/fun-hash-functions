//
//  Hasher.cpp
//  Hasher implementation
//
//  Created by Daniel Vasquez on 2013-06-18.
//  Copyright (c) 2013 Daniel Vasquez & Parham Rahmani. All rights reserved.
//

#include "Hasher.h"
#include <math.h>
#include <fstream>
#include <iomanip>



// See assignment description.
Hasher::Hasher(char hashType, char probeType){
    this->hashType = hashType;
    this->probeType = probeType;
    numProbes = 0;
    table = new TableEntry*[TABLE_SIZE];

};
// See assignment description.
Hasher::Hasher(char hashType, char probeType, double loadFactor, char* fileName){
    this->hashType = hashType;
    this->probeType = probeType;
    this->loadFactor = loadFactor;
    this->fileName = fileName;
    this->hashTableSize = generateTableSize(this->fileName);
    numProbes = 0;
    table = new TableEntry*[hashTableSize];
};

Hasher::~Hasher(){
    for (int i = 0; i < TABLE_SIZE; i++)
        if (table[i] != NULL)
            delete table[i];
    delete[] table;
}

// Private helper functions:

// TODO: Implement this! Temporarily using code from http://stackoverflow.com/a/107657
unsigned int Hasher::goodHash(std::string key){
    const char* s = key.c_str();
    unsigned hash = 0;
    while (*s)
    {
        hash = hash * 101  +  *s++;
    }
    return hash % TABLE_SIZE;
}

// Takes a string key and generates a hash number by taking the sum of its ASCII character values
unsigned int Hasher::poorHash(std::string key){
    int sum = 0;
    for(int i = 0; i < key.size(); i++){
        sum += key[i]+0;
    }
    return sum % TABLE_SIZE;
}

// Returns the key stored at given subscript.
const std::string Hasher::getKey(const int subscript){
    return table[subscript]->getKey();

};

// Returns the data value at given subscript.
const int Hasher::getValue(const int subscript){
    return table[subscript]->getValue();
};

// Returns the number of probes.
const int Hasher::getProbes(void){
    return numProbes;
};

// Returns the hashTableSize.
const int Hasher::getCapacity(void){
    return hashTableSize;
};

// Returns the number of non-empty elements.
const int getSize(void);

// isPrime modified from an algorithm written by Francesco Balena
// downloaded from http://www.devx.com/vb2themax/Tip/19051
/** @pre x>0
 *  @post if x was prime, true returned, else false
 */
const bool Hasher::isPrime(const int x){
    if (x == 1 || x == 2 || x == 3 || x == 5) return true; if (x % 2 == 0 || x % 3 == 0) { return false; }
    int incr = 4; // NOTE: sqrt needs #include <math.h>
    const int maxFact = (int) sqrt( (double) x );
    for (int fact = 5; fact <= maxFact; fact += incr) { if (x % fact == 0) { return false; }
        incr = 6 - incr;
    }
    return true;
}

// Reads a file, determines the number of records, and returns
// the next prime number greater than 2 * the number of records
int Hasher::generateTableSize(char* filename){
    int num = 0;
    std::string line;
    std::ifstream infile (filename);
    if (infile.is_open())
    {
        while ( infile.good() )
        {
            getline (infile,line);
            if( not line.empty() ) num++;
        }
        infile.close();
        std::cout << num << " records found in " << fileName << std::endl;
    }
    else std::cout << "Unable to open file" << std::endl;

    num = num * 2; // double the size for more room in the table
    while(not isPrime(num)){
        num++;
    }
    return num; // return a prime number 
}



// Define the following functions:

// See assignment description.
bool Hasher::search(std::string key, int& subscript){return false;};
// See assignment description.
bool Hasher::insert(std::string key, int value){return false;};
// See assignment description.
bool Hasher::remove(std::string key){return false;};

bool Hasher::isFull(){return false;};

// Simply outputs the current contents of the table and the indices (you can write a loop
// that just prints out the underlying array):
// E.g.
//    table->printTable() might generate:
//        25  HBZEJKGA   1
//        32  RHJMIVTA   2
//
void Hasher::printTable(){
    
    for(int i = 0; i < hashTableSize; i++){
        TableEntry* entry = table[i];
        if(entry != NULL) std::cout << std::setw(3) << i << entry->getKey() << entry->getValue();
    }
}

// Define any other necessary functions that are part of the public interface:




