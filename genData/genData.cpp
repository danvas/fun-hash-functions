// Course:  CPSC 221
// File:    genData.cpp
// Authors: Daniel Vasquez - 36421089 - n7o8
//          Parham Rahmani -  -
// Date:    June 16, 2013
//

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, const char* argv[])
{
    
    int numRecords;
    string fname;
    /*
     // For debugging (DELETE WHEN READY TO DELIVER)
     cout << "numRecords = " << numRecords << "  " <<typeid(numRecords).name() <<endl;
     cout << "fname = " << fname << endl;
     cout << "fname[8] = " << fname[8] << endl;
     cout << "fname.size() = " << fname.size() << endl;
     
     
     for ( int i = 0; i < argc; i++){
     const char* val = argv[i];
     cout << i << ": "<< val << " " << typeid(val).name() << endl;
     }
     */ // debugging code
    
    // Input values from command line arguments (uncomment for delivery)
//    numRecords = atoi(argv[1]);
//    fname = argv[2];
    
    // Default values (uncomment for testing phase)
    numRecords = 25;
    fname = "small.txt";
    


    
    string wdir = "/Users/danvas/Google Drive/School/BCS/CPSC/221/Dev/Assignment2/";

//    string outfile = wdir + fname;
//    
//    string line;
//    ifstream mazefile (outfile.c_str()); // .c_str needed to compile in gcc!
//    
//    char maze[SIZE][SIZE];
//    for( int row = 0 ; row < SIZE ; row++ ){
//        for (int col = 0 ; col < SIZE ; col++ ){
//            maze[row][col] = '0'; // initialize all to null character
//            //cout << maze[row][col];
//        }
//        //cout << endl;
//    }
//    int row = 0;
//    Point start;
//    
//    if (mazefile.is_open()){ // build maze array
//        while ( mazefile.good() ){
//            getline (mazefile,line);
//            char* ptrLine = (char*)line.c_str();
//            for(int col = 0; col < line.size(); col++){
//                maze[row][col] = ptrLine[col];
//                //cout << maze[row][col];
//                if(maze[row][col] == 'S') { // get starting point
//                    start.x = row;
//                    start.y = col;
//                }
//            }
//            row++;
//            //cout << endl;
//        }
//        mazefile.close();
//    } else {
//        cout << "// File is not open. NULL return";
//        return NULL;
//    }
    
    return 0;
}

