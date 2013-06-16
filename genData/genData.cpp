// Course:  CPSC 221
// File:    genData.cpp
// Authors: Daniel Vasquez - 36421089 - n7o8
//          Parham Rahmani -  -
// Date:    June 16, 2013
//

#include <iostream>
#include <ofstream>


using namespace std;

int main(int argc, const char * argv[])
{
    string wdir = "/Users/danvas/Google Drive/School/BCS/CPSC/221/Dev/Assignment2/Assignment2/"
    int numRecords = 25;
    
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
    
    return 0;
}

