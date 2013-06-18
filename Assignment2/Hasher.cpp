//
//  Hasher.cpp
//  hashDriver
//
//  Created by Daniel Vasquez on 2013-06-18.
//  Copyright (c) 2013 Daniel Vasquez & Parham Rahmani. All rights reserved.
//

#include "Hasher.h"

// See assignment description.
Hasher::Hasher(char type, char crp){};
// See assignment description.
Hasher::Hasher(char type, char crp, char* filename){};

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




