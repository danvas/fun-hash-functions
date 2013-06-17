//
//  SplitString.h
//  hashDriver
//
//  Created by Daniel Vasquez on 2013-06-16.
//  Copyright (c) 2013 Daniel Vasquez & Parham Rahmani. 
//

// Code derived from http://www.cplusplus.com/articles/1UqpX9L8/

#ifndef __hashDriver__SplitString__
#define __hashDriver__SplitString__

#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Class splitstring which adds method split()

class SplitString : public string {
    vector<string> flds;
public:
    SplitString(string s) : string(s) { };
    vector<string>& split(char delim, int rep=0);
};

#endif /* defined(__hashDriver__SplitString__) */
