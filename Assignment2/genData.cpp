//
//  genData.cpp
//  Assignment2
//
//  Created by Daniel Vasquez & Parham Rahmani on 2013-06-15.
//  Copyright (c) 2013 Daniel Vasquez & Parham Rahmani. All rights reserved.
//

#include "genData.h"


string wdir = "/Users/danvas/Google Drive/School/BCS/CPSC/221/Dev/Assignment2/Assignment2/"

string fname = "genData25small.txt";
string infile = wdir + fname;
string line;
ifstream mazefile (infile.c_str()); // .c_str needed to compile in gcc!

char maze[SIZE][SIZE];
for( int row = 0 ; row < SIZE ; row++ ){
    for (int col = 0 ; col < SIZE ; col++ ){
        maze[row][col] = '0'; // initialize all to null character
        //cout << maze[row][col];
    }
    //cout << endl;
}
int row = 0;
Point start;

if (mazefile.is_open()){ // build maze array
    while ( mazefile.good() ){
        getline (mazefile,line);
        char* ptrLine = (char*)line.c_str();
        for(int col = 0; col < line.size(); col++){
            maze[row][col] = ptrLine[col];
            //cout << maze[row][col];
            if(maze[row][col] == 'S') { // get starting point
                start.x = row;
                start.y = col;
            }
        }
        row++;
        //cout << endl;
    }
    mazefile.close();
} else {
    cout << "// File is not open. NULL return";
    return NULL;
}