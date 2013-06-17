// Course:  CPSC 221
// File:    hashDriver.cpp
// Authors: Daniel Vasquez - 36421089 - n7o8
//          Parham Rahmani -  -
// Date:    June 16, 2013


#include <iostream>
#include <cstdlib>
#include <fstream>
#include "SplitString.h"
#include <cxxabi.h> // for demangling/debugging


using namespace std;

unsigned int goodHash(string key);
unsigned int poorHash(string key);
void displayPoorHash();
void displayGoodHash();

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
    char delim = '\t';
    string line;
    ifstream infile ("small.txt");
    if (infile.is_open())
    {
        while ( infile.good() )
        {
            getline (infile,line);
            
            
            if (not line.empty()){
                SplitString keyValue(line);
                vector<string> key = keyValue.split(delim);
                cout << key[0] << "\t" << poorHash(key[0]) << endl;
            }
        }
        infile.close();
    }
    else cout << "Unable to open file";
    cout << endl;

}

// Prints out the results of using goodHash function on file small.txt
void displayGoodHash(){
    char delim = '\t';
    string line;
    ifstream infile ("small.txt");
    if (infile.is_open())
    {
        while ( infile.good() )
        {
            getline (infile,line);
            if (not line.empty()){
                SplitString keyValue(line);
                vector<string> key = keyValue.split(delim);
                cout << key[0] << "\t" << goodHash(key[0]) << endl;
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