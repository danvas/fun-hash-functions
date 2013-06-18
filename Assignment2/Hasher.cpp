//
//  Hasher.cpp
//  Hasher implementation
//
//  Created by Daniel Vasquez on 2013-06-18.
//  Copyright (c) 2013 Daniel Vasquez & Parham Rahmani. All rights reserved.
//

#include "Hasher.h"

// See assignment description.
Hasher::Hasher(char type, char crp){};
// See assignment description.
Hasher::Hasher(char type, char crp, char* filename){};

// Helper functions:

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
void Hasher::printTable(){};

// Define any other necessary functions that are part of the public interface:




