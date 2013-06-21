// Course:  CPSC 221
// File:    genData.cpp
// Authors: Daniel Vasquez - 36421089 - n7o8
//          Parham Rahmani -  -
// Date:    June 16, 2013
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h> // for random seeding
#include <string>
#include <sstream>
#include <cxxabi.h> // for demangling/debugging
using namespace std;

string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, const char* argv[])
{
    srand(time(0));
    
    // Variables
    const int numLettersInKey = 8;
    int numRecords;
    const char* filename;
    string delim = "\t"; // Tab space separating key and value in a line
    
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
    numRecords = atoi(argv[1]);
    filename = argv[2];
    
    // Default values (uncomment for development phase)
//    numRecords = 25;
//    filename = "small.txt";
    
    ofstream outfile;
    outfile.open(filename);
    if (outfile.is_open()) {
        // Loop to generate key-value pairs in a file
        for (int n = 0; n < numRecords; n++){
            
            // Generate key with 8 letters
            string key;
            for(int i = 0; i < numLettersInKey; i++) {
                stringstream ss;
                string s;
                ss << letters[rand()%26];
                ss >> s;
                key.append(s);
            }
            
            /*
             // Print type of data (DELETE WHEN READY TO DELIVER)
             int success;
             char *realname = abi::__cxa_demangle(typeid(key).name(), 0, 0, &success);
             cout << realname << endl;
             */ // debugging code

            outfile << key << delim << n+1 << endl;
            //cout << n+1 << "\t" << key << endl;
        }
        outfile.close();
    } else cout << "Error: File not opened";
    
    return 0;
}

