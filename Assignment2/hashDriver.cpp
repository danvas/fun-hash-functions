// Course:  CPSC 221
// File:    hashDriver.cpp
// Authors: Daniel Vasquez - 36421089 - n7o8
//          Parham Rahmani -  -
// Date:    June 16, 2013


#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <cxxabi.h> // for demangling/debugging
#include "Hasher.h"


using namespace std;

unsigned int goodHash(string key);
unsigned int poorHash(string key);
void displayPoorHash();
void displayGoodHash();


// **Sample** main function/driver-- THIS IS NOT A COMPLETE TEST SUITE
// YOU MUST WRITE YOUR OWN TESTS
// See assignment description.
int main( int argc, char* argv[])
{
    /*
    // Generate empty hash tables:
    Hasher* goodHashRP1 = new Hasher('g', 'd');
    Hasher* goodHashQP1 = new Hasher('g', 'q');
    Hasher* badHashRP1 = new Hasher('b', 'd');
    Hasher* badHashQP1 = new Hasher('b', 'q');
    
    // Generate hash tables that are systematically loaded from file.
    // Note that if you cannot fit an element you should stop inserting elements
    // and set a flag to full.
    Hasher* goodHashRP2 = new Hasher('g', 'd', 0.25, "filename.txt");
    Hasher* goodHashQP2 = new Hasher('g', 'q', 0.5, "filename.txt");
    Hasher* poorHashRP2 = new Hasher('b', 'd', 0.75, "filename.txt");
    Hasher* poorHashQP2 = new Hasher('b', 'q', 0.25, "filename.txt");
    
    // Sample use case:
    std::string key = "HBZEJKGA";
    int value = 10;
    if(goodHashRP1->insert(key, value)) 
        std::cout << "Inserted" << std::endl;
    else
        std::cout << "Failed to insert" << std::endl;
    
    int subscript = -1; 
    
    if(goodHashRP1->search(key, subscript)) 
        std::cout << "Found at " << subscript << std::endl;
    else
        std::cout << "Failed to insert" << std::endl;
    
    if(goodHashRP1->remove(key)) 
        std::cout << "Removed" << std::endl;
    else
        std::cout << "Not deleted/not found" << std::endl;
    
    
    goodHashRP1->printTable();
    */ // Original code commented out while writing Part 2
    
    cout << "poorHash: " << endl;
    displayPoorHash();
    cout << "goodHash: " << endl;
    displayGoodHash();

    return 0;
}

// Prints out the results of using poorHash function on file small.txt
void displayPoorHash(){
    string line;
    ifstream infile ("small.txt");
    if (infile.is_open())
    {
        while ( infile.good() )
        {
            getline (infile,line);
            
            // Tokenize string using strtok
            if(not line.empty()){
                char* chr = strdup(line.c_str()); // Convert string to char
                char * pch;
                pch = strtok(chr, "\t"); //s Tokenize string by delimiter "\t"
                cout << pch << "\t" << poorHash(pch) << endl;
                free(chr);
            }
        }
        infile.close();
    }
    else cout << "Unable to open file";
    cout << endl;

}

// Prints out the results of using goodHash function on file small.txt
void displayGoodHash(){
    string line;
    ifstream infile ("small.txt"); // TODO: Make this a command line argument
    if (infile.is_open())
    {
        while ( infile.good() )
        {
            getline (infile,line);
            
            // Tokenize string using strtok
            if(not line.empty()){
                char* chr = strdup(line.c_str()); // Convert string to char
                char * pch;
                pch = strtok(chr, "\t"); // Tokenize string by delimiter "\t"
                cout << pch << "\t" << goodHash(pch) << endl;
                free(chr);
            }
        }
        infile.close();
    }
    else cout << "Unable to open file";
    cout << endl;

}

// TODO: Implement this! Temporarily using code from http://stackoverflow.com/a/107657 
unsigned int goodHash(string key){
    const char* s = key.c_str();
    unsigned hash = 0;
    while (*s)
    {
        hash = hash * 101  +  *s++;
    }
    return hash % TABLE_SIZE;
}

// Takes a string key and generates a hash number by taking the sum of its ASCII character values 
unsigned int poorHash(string key){
    int sum = 0;
    for(int i = 0; i < key.size(); i++){
        sum += key[i]+0;
    }
    return sum % TABLE_SIZE;
}