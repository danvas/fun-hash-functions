// Course:  CPSC 221
// File:    hashDriver.cpp
// Authors: Daniel Vasquez - 36421089 - n7o8
//          Parham Rahmani -  -
// Date:    June 16, 2013


#include <iostream>
#include <iomanip>
#include <string>


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
    
    return 0;
}