//
//  Hasher.h
//  Hasher class definition
//
//  Created by Daniel Vasquez on 2013-06-18.
//  Copyright (c) 2013 Daniel Vasquez & Parham Rahmani. All rights reserved.
//

#ifndef __hashDriver__Hasher__
#define __hashDriver__Hasher__

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstring>

class TableEntry {
private:
    std::string key;
    int value;
public:
    TableEntry(std::string key, int value) {
        this->key = key;
        this->value = value;
    }
    
    std::string getKey() { return key; }
    int getValue() { return value; }
    
};




#define TABLE_SIZE 100 // Change as necessary

#define TOMBSTONE new TableEntry("zzzzzzzz", -1)

class Hasher {
    
private:
    TableEntry** table;
    
    char hashType;
    char probeType;
    double loadFactor;
    char* fileName;
    int hashTableSize;
    int numProbes;
    int numEntries;

    
    
    // Define any other necessary helper functions that are not part of the public interface:
    
    unsigned int goodHash(std::string key);
    unsigned int poorHash(std::string key);
    unsigned int altHash(std::string key);
    
    // Returns the key stored at given subscript.
    const std::string getKey(const int);
    
    // Returns the data value at given subscript.
    const int getValue(const int);
    
    // Returns the number of probes.
    const int getProbes(void);
    
    // Returns the hashTableSize.
    const int getCapacity(void);
    
    // Returns the number of non-empty elements. 
    const int getSize(void);
    
    // Check for prime number
    const bool isPrime(const int);
    
    int generateTableSize(char*);
    
//    /** Expand the table size when load_factor exceeds LOAD_THRESHOLD.
//     post: The size of the table is doubled.
//     Each nondeleted entry from the original table is
//     reinserted into the expanded table.
//     The value of num_keys is reset to the number of items
//     actually inserted; num_deletes is reset to 0.
//     */
//    void rehash();

    
    
public:
    // Necessary constructors (be sure to initialize your table entries to NULL):
    
    // hashType is either g (for good) or p (for poor)
    // probeType is either d (for double) or q (for quadratic)
    // loadFactor is the load factor (eg: 0.25)
    // fileName is the name of the input file (eg: small.txt) used
    Hasher(char hashType, char probeType);
    // See assignment description.
    Hasher(char hashType, char probeType, double loadFactor, char* fileName);
     
    // Define the following functions:
    
    // See assignment description.
    bool search(std::string key, int& subscript);
    // See assignment description.
    bool insert(std::string key, int value);
    // See assignment description.
    bool remove(std::string key);
    
    bool isFull();
    
    // Simply outputs the current contents of the table and the indices (you can write a loop
    // that just prints out the underlying array):
    // E.g.
    //    table->printTable() might generate:
    //        25  HBZEJKGA   1
    //        32  RHJMIVTA   2
    //
    void printTable();
    
    // Define any other necessary functions that are part of the public interface:
    
    // Destructor-- do not alter.
    ~Hasher();
    
};


#endif /* defined(__hashDriver__Hasher__) */
