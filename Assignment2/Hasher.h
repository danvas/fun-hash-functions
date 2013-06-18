//
//  Hasher.h
//  hashDriver
//
//  Created by Daniel Vasquez on 2013-06-18.
//  Copyright (c) 2013 Daniel Vasquez & Parham Rahmani. All rights reserved.
//

#ifndef __hashDriver__Hasher__
#define __hashDriver__Hasher__

#include <iostream>

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
class Hasher {
private:
    TableEntry** table;
    
    // Define any other necessary helper functions that are not part of the public interface:
    
public:
    // Define the necessary constructors (be sure to initialize your table entries to NULL):
    
    // See assignment description.
    Hasher(char type, char crp);
    // See assignment description.
    Hasher(char type, char crp, char* filename);
    
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
    ~Hasher()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
            if (table[i] != NULL)
                delete table[i];
        delete[] table;
    }
    
};


#endif /* defined(__hashDriver__Hasher__) */
