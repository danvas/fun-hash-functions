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
#include <cxxabi.h> // for demangling/debugging




// See assignment description.
Hasher::Hasher(char hashType, char probeType){
    this->hashType = hashType;
    this->probeType = probeType;
    numProbes = 0;
    hashTableSize = TABLE_SIZE;
    table = new TableEntry*[hashTableSize];
    numEntries = 0;

}
// See assignment description.
Hasher::Hasher(char hashType, char probeType, double loadFactor, char* fileName){
    this->hashType = hashType;
    this->probeType = probeType;
    this->loadFactor = loadFactor;
    this->fileName = fileName;
    this->hashTableSize = generateTableSize(this->fileName);
    numProbes = 0;
    table = new TableEntry*[hashTableSize];
    for (int i=0; i < hashTableSize; i++){
        table[i] = NULL;
    }

}

Hasher::~Hasher(){
    for (int i = 0; i < TABLE_SIZE; i++)
        if (table[i] != NULL)
            delete table[i];
    delete[] table;
}

// Private helper functions:

/** Hashes and compresses key using good algorithm
 *  @pre  key is of type string and is non-empty
 *  @post Computes a summation of the ASCII character values of key,
 *        incorporating a prime number, and returns the unsigned 
 *        integer result modulo size of table
 */
unsigned int Hasher::goodHash(std::string key){
    const char* s = key.c_str();
    unsigned hash = 0;
    while (*s)
    {
        hash = hash * 101  +  *s++;
    }
    return hash % hashTableSize;
}

/** Hashes and compresses key using poor algorithm
 *  @pre  key is of type string and is non-empty
 *  @post iterates through characters of key and returns the unsigned
 *        integer sum of their ASCII character values modulo size of table
 */
unsigned int Hasher::poorHash(std::string key){
    int hash = 0;
    for(int i = 0; i < key.size(); i++){
        hash += key[i]+0;
    }
    return hash % hashTableSize;
}


/** Hashes and compresses key using good algorithm
 *  @pre  key is of type string and is non-empty
 *  @post Computes a summation of the ASCII character values of key,
 *        incorporating a prime number, and returns the unsigned
 *        integer result modulo size of table
 */
unsigned int Hasher::altHash(std::string key){
    const char* s = key.c_str();
    unsigned hash = 0;
    while (*s)
    {
        hash = hash * 103  +  *s++;
    }
    return hash % hashTableSize;
}




// Returns the key stored at given subscript.
const std::string Hasher::getKey(const int subscript){
    return table[subscript]->getKey();

}

// Returns the data value at given subscript.
const int Hasher::getValue(const int subscript){
    return table[subscript]->getValue();
}

// Returns the number of probes.
const int Hasher::getProbes(void){
    return numProbes;
}

// Returns the hashTableSize.
const int Hasher::getCapacity(void){
    return hashTableSize;
}

// Returns the number of non-empty elements.
const int Hasher::getSize(void){
    return numEntries;
}

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


// Reads a file, determines the number of records, and generates an prime integer 
// representing a table size that would accommodate for a hash map
/** @pre  filename is a pointer to a character and is the name of the file to be read
 *  @post counts the number of non-empty lines in the file, doubles it, increments up to 
 *        the next prime number and returns the result, an integer
 */
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
bool Hasher::search(std::string key, int& subscript){ // for goodHash
    
    bool isFound = true;
    
    bool tombFound = false;
    int firstTomb;
    
    
    //  GOOD HASH AND QUAD PROBE
    if (this->hashType == 'g' && this->probeType == 'q'){
        int index = goodHash(key) % hashTableSize;
        
        if (table[index] == NULL){
            isFound = false;
            subscript = index;
            numProbes++;
            return isFound;
        }
        
        else if (this->getKey(index) == key){
            subscript = index;
            numProbes++;
            return isFound;
        }
        
        
        else {
            while (key != this->getKey(index)){
                if(numProbes == hashTableSize){
                    isFound = false;
                    break;
                }
                if (table[index] == TOMBSTONE){
                    tombFound = true;
                    firstTomb = index;
                }
                numProbes++;
                index = (index + numProbes * numProbes % hashTableSize);
                
            }
            
        }
        if(isFound)
            subscript = index;
        
    }
    
    
    
    //  POOR HASH AND QUAD PROBE
    if (this->hashType == 'p' && this->probeType == 'q'){
        int index = poorHash(key) % hashTableSize;
        
        if (table[index] == NULL){
            isFound = false;
            subscript = index;
            numProbes++;
            return isFound;
        }
        
        else if (this->getKey(index) == key){
            subscript = index;
            numProbes++;
            return isFound;
        }
        
        
        else {
            while (key != this->getKey(index)){
                if(numProbes == hashTableSize){
                    isFound = false;
                    break;
                }
                if (table[index] == TOMBSTONE){
                    tombFound = true;
                    firstTomb = index;
                }
                numProbes++;
                index = (index + numProbes * numProbes % hashTableSize);
                
            }
            
        }
        if(isFound)
            subscript = index;
    }
    
    //  GOOD HASH AND DOUBLE PROBE
    if (this->hashType == 'p' && this->probeType == 'd'){
        int index = goodHash(key) % hashTableSize;
        
        if (table[index] == NULL){
            isFound = false;
            subscript = index;
            numProbes++;
            return isFound;
        }
        
        else if (this->getKey(index) == key){
            subscript = index;
            numProbes++;
            return isFound;
        }
        
        
        else {
            while (key != this->getKey(index)){
                if(numProbes == hashTableSize){
                    isFound = false;
                    break;
                }
                if (table[index] == TOMBSTONE){
                    tombFound = true;
                    firstTomb = index;
                }
                numProbes++;
                index = (index + numProbes * numProbes % hashTableSize);
                
            }
            
        }
        if(isFound)
            subscript = index;
        
    }
    
    //  POOR HASH AND DOUBLE PROBE
    if (this->hashType == 'g' && this->probeType == 'd'){
        int index = poorHash(key) % hashTableSize;
        
        if (table[index] == NULL){
            isFound = false;
            subscript = index;
            numProbes++;
            return isFound;
        }
        
        else if (this->getKey(index) == key){
            subscript = index;
            numProbes++;
            return isFound;
        }
        
        
        else {
            while (key != this->getKey(index)){
                if(numProbes == hashTableSize){
                    isFound = false;
                    break;
                }
                if (table[index] == TOMBSTONE){
                    tombFound = true;
                    firstTomb = index;
                }
                numProbes++;
                index = (index + numProbes * numProbes % hashTableSize);
                
            }
            
        }
        if(isFound)
            subscript = index;
        
    }
    
    
    return isFound;
}



// See assignment description.
bool Hasher::insert(std::string key, int value){
    
//    double loadFactor = numEntries / TABLE_SIZE;
//
//    if (loadFactor > LOAD_THRESHOLD) {
//        rehash(); // Double the size of the table.
//    }
    int subs = -1;
    search(key, subs);
    TableEntry* newEntry = new TableEntry(key, value);
    table[subs] = newEntry;
    
    return true;

}

// See assignment description.
bool Hasher::remove(std::string key){
    
//    int index = -1;
//    bool found = search(key,index);
//    
//    if(found) table[index] = TOMBSTONE;
//    numEntries--;
//    return found;
    return false;

};

bool Hasher::isFull(){
    return (numEntries == hashTableSize);
    
}

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
        if(entry != NULL) std::cout
                         << i << " " << entry->getKey()<< " " << entry->getValue()
                         << std::endl;
    }
}

// Define any other necessary functions that are part of the public interface:




