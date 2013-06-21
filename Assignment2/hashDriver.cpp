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
#include <math.h>
#include <iomanip>
#include "Hasher.h"

/*
using namespace std;


class TableEntry {
private:
    string key;
    int value;
public:
    TableEntry(string key, int value) {
        this->key = key;
        this->value = value;
    }
    
    std::string getKey() { return key; }
    int getValue() { return value; }
    
};






#define TABLE_SIZE 100 // Change as necessary

#define TOMBSTONE (new TableEntry("zzzzzzzz", 0))



class Hasher {
private:
    TableEntry** table;
    
    // Define any other necessary helper functions that are not part of the public interface:
    
    unsigned int goodHash();
    unsigned int poorHash();
    
    
    char hashType;
    char probeType;
    double loadFactor;
    char* fileName;
    int hashTableSize;
    int numProbes;
    
    
    
    
    
    
public:
    // Define the necessary constructors (be sure to initialize your table entries to NULL):
    
    Hasher(char hashType, char probeType){
        this->hashType = hashType;
        this->probeType = probeType;
        numProbes = 0;
        table = new TableEntry*[TABLE_SIZE];
        hashTableSize = TABLE_SIZE;
        for (int i=0; i < hashTableSize; i++){
            table[i] = NULL;
        }
        
    }
    
    Hasher(char hashType, char probeType, double loadFactor, char* fileName){
        this->hashType = hashType;
        this->probeType = probeType;
        this->loadFactor = loadFactor;
        this->fileName = fileName;
        this->hashTableSize = generateTableSize(this->fileName);
        numProbes = 0;
        table = new TableEntry*[hashTableSize];
        for (int i=0; i < hashTableSize; i++){
            table[i] = NULL;
        }
    };
    
    
    
    
    // Destructor-- do not alter.
    ~Hasher()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
            if (table[i] != NULL)
                delete table[i];
        delete[] table;
    }
    
    unsigned int goodHash(std::string key){
        const char* s = key.c_str();
        unsigned hash = 0;
        while (*s)
        {
            hash = hash * 101  +  *s++;
        }
        return hash % hashTableSize;
    }
    
    unsigned int altHash(std::string key){
        const char* s = key.c_str();
        unsigned hash = 0;
        while (*s)
        {
            hash = hash * 103  +  *s++;
        }
        return hash % hashTableSize;
    }
    // Takes a string key and generates a hash number by taking the sum of its ASCII character values
    unsigned int poorHash(std::string key){
        int sum = 0;
        for(int i = 0; i < key.size(); i++){
            sum += key[i]+0;
        }
        return sum % hashTableSize;
    }
    
    // Returns the key stored at given subscript.
    const std::string getKey(const int subscript){
        return table[subscript]->getKey();
        
    };
    
    // Returns the data value at given subscript.
    const int getValue(const int subscript){
        return table[subscript]->getValue();
    };
    
    // Returns the number of probes.
    const int getProbes(void){
        return numProbes;
    };
    
    // Returns the hashTableSize.
    const int getCapacity(void){
        return hashTableSize;
    };
    
    // Returns the number of non-empty elements.
    const int getSize(void);
    
    // isPrime modified from an algorithm written by Francesco Balena
    // downloaded from http://www.devx.com/vb2themax/Tip/19051
    * @pre x>0
     *  @post if x was prime, true returned, else false
     
    const bool isPrime(const int x){
        if (x == 1 || x == 2 || x == 3 || x == 5) return true; if (x % 2 == 0 || x % 3 == 0) { return false; }
        int incr = 4; // NOTE: sqrt needs #include <math.h>
        const int maxFact = (int) sqrt( (double) x );
        for (int fact = 5; fact <= maxFact; fact += incr) { if (x % fact == 0) { return false; }
            incr = 6 - incr;
        }
        return true;
    }
    
    // Reads a file, determines the number of records, and returns
    // the next prime number greater than 2 * the number of records
    int generateTableSize(char* filename){
        int num = 0;
        std::string line;
        std::ifstream infile (filename);
        if (infile.is_open())
        {
            while ( infile.good() )
            {
                getline (infile,line);
                if( not line.empty() ) num++;
            }
            infile.close();
            std::cout << num << " records found in " << fileName << std::endl;
        }
        else std::cout << "Unable to open file" << std::endl;
        
        num = num * 2; // double the size for more room in the table
        while(not isPrime(num)){
            num++;
        }
        return num; // return a prime number
    }
    
    
    
    
    
    // Define the following functions:
    
    // See assignment description.
    bool search(string key, int& subscript){
        
        bool isFound = true;
        
        bool tombFound = false;
        int firstTomb;
        
        
        //  GOOD HASH AND QUAD PROBE
        if (this->hashType == 'g' && this->probeType == 'q'){
            int index = goodHash(key) % hashTableSize;
            
            if (table[index] == NULL){
                isFound = false;
                subscript = index;
                numProbes++;
                return isFound;
            }
            
            else if (this->getKey(index) == key){
                subscript = index;
                numProbes++;
                return isFound;
            }
            
            
            else {
                while (key != this->getKey(index)){
                    if(numProbes == hashTableSize){
                        isFound = false;
                        break;
                    }
                    if (table[index] == TOMBSTONE){
                        tombFound = true;
                        firstTomb = index;
                    }
                    numProbes++;
                    index = (index + numProbes * numProbes % hashTableSize);
                    
                }
                
            }
            if(isFound)
                subscript = index;
            
        }
        
        
        
        //  POOR HASH AND QUAD PROBE
        if (this->hashType == 'p' && this->probeType == 'q'){
            int index = poorHash(key) % hashTableSize;
            
            if (table[index] == NULL){
                isFound = false;
                subscript = index;
                numProbes++;
                return isFound;
            }
            
            else if (this->getKey(index) == key){
                subscript = index;
                numProbes++;
                return isFound;
            }
            
            
            else {
                while (key != this->getKey(index)){
                    if(numProbes == hashTableSize){
                        isFound = false;
                        break;
                    }
                    if (table[index] == TOMBSTONE){
                        tombFound = true;
                        firstTomb = index;
                    }
                    numProbes++;
                    index = (index + numProbes * numProbes % hashTableSize);
                    
                }
                
            }
            if(isFound)
                subscript = index;
        }
        
        //  GOOD HASH AND DOUBLE PROBE
        if (this->hashType == 'p' && this->probeType == 'd'){
            int index = goodHash(key) % hashTableSize;
            
            if (table[index] == NULL){
                isFound = false;
                subscript = index;
                numProbes++;
                return isFound;
            }
            
            else if (this->getKey(index) == key){
                subscript = index;
                numProbes++;
                return isFound;
            }
            
            
            else {
                while (key != this->getKey(index)){
                    if(numProbes == hashTableSize){
                        isFound = false;
                        break;
                    }
                    if (table[index] == TOMBSTONE){
                        tombFound = true;
                        firstTomb = index;
                    }
                    numProbes++;
                    index = (index + numProbes * numProbes % hashTableSize);
                    
                }
                
            }
            if(isFound)
                subscript = index;
            
        }
        
        //  POOR HASH AND DOUBLE PROBE
        if (this->hashType == 'g' && this->probeType == 'd'){
            int index = poorHash(key) % hashTableSize;
            
            if (table[index] == NULL){
                isFound = false;
                subscript = index;
                numProbes++;
                return isFound;
            }
            
            else if (this->getKey(index) == key){
                subscript = index;
                numProbes++;
                return isFound;
            }
            
            
            else {
                while (key != this->getKey(index)){
                    if(numProbes == hashTableSize){
                        isFound = false;
                        break;
                    }
                    if (table[index] == TOMBSTONE){
                        tombFound = true;
                        firstTomb = index;
                    }
                    numProbes++;
                    index = (index + numProbes * numProbes % hashTableSize);
                    
                }
                
            }
            if(isFound)
                subscript = index;
            
        }
        
        
        return isFound;
    }
    
    
    
    // See assignment description.
    bool insert(string key, int value){
        int subs = -1;
        search(key, subs);
        TableEntry* newEntry = new TableEntry(key, value);
        table[subs] = newEntry;
        
        return true;
    };
    // See assignment description.
    bool remove(string key){return false;};
    
    bool isFull(){return false;};
    
    // Simply outputs the current contents of the table and the indices (you can write a loop
    // that just prints out the underlying array):
    // E.g.
    //    table->printTable() might generate:
    //        25  HBZEJKGA   1
    //        32  RHJMIVTA   2
    //
    void printTable(){
        
        for(int i = 0; i < hashTableSize; i++){
            TableEntry* entry = table[i];
            if(entry != NULL) cout << setw(3) << i << entry->getKey() << setw(3) << entry->getValue() << endl;
        }
    }
};


*/





// Private helper functions:


// TODO: Implement this! Temporarily using code from http://stackoverflow.com/a/107657


// Define any other necessary functions that are part of the public interface:
// **Sample** main function/driver-- THIS IS NOT A COMPLETE TEST SUITE
// YOU MUST WRITE YOUR OWN TESTS
// See assignment description.
int main( int argc, char* argv[])
{
    ///*
    // Generate empty hash tables:
    Hasher* goodHashRP1 = new Hasher('g', 'd');
    Hasher* goodHashQP1 = new Hasher('g', 'q');
    Hasher* badHashRP1 = new Hasher('p', 'd');
    Hasher* badHashQP1 = new Hasher('p', 'q');
    
    // Generate hash tables that are systematically loaded from file.
    // Note that if you cannot fit an element you should stop inserting elements
    // and set a flag to full.
    //    Hasher* goodHashRP2 = new Hasher('g', 'd', 0.25, "small.txt");
    //    Hasher* goodHashQP2 = new Hasher('g', 'q', 0.5, "small.txt");
    //    Hasher* poorHashRP2 = new Hasher('b', 'd', 0.75, "small.txt");
    //    Hasher* poorHashQP2 = new Hasher('b', 'q', 0.25, "small.txt");
    
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
    
    key = "HBZEJDTA";
    value = 20;
    if(goodHashQP1->insert(key, value))
        std::cout << "Inserted" << std::endl;
    else
        std::cout << "Failed to insert" << std::endl;
    
    subscript = -1;
    
    if(goodHashQP1->search(key, subscript))
        std::cout << "Found at " << subscript << std::endl;
    else
        std::cout << "Failed to insert" << std::endl;
    
    if(goodHashQP1->remove(key))
        std::cout << "Removed" << std::endl;
    else
        std::cout << "Not deleted/not found" << std::endl;
    
    
    goodHashQP1->printTable();
    
    
    key = "FGYEJDTB";
    value = 40;
    if(badHashRP1->insert(key, value))
        std::cout << "Inserted" << std::endl;
    else
        std::cout << "Failed to insert" << std::endl;
    
    subscript = -1;
    
    if(badHashRP1->search(key, subscript))
        std::cout << "Found at " << subscript << std::endl;
    else
        std::cout << "Failed to insert" << std::endl;
    
    if(badHashRP1->remove(key))
        std::cout << "Removed" << std::endl;
    else
        std::cout << "Not deleted/not found" << std::endl;
    
    
    badHashRP1->printTable();
    
    key = "IGHDTERO";
    value = 50;
    if(badHashQP1->insert(key, value))
        std::cout << "Inserted" << std::endl;
    else
        std::cout << "Failed to insert" << std::endl;
    
    subscript = -1;
    
    if(badHashQP1->search(key, subscript))
        std::cout << "Found at " << subscript << std::endl;
    else
        std::cout << "Failed to insert" << std::endl;
    
    if(badHashQP1->remove(key))
        std::cout << "Removed" << std::endl;
    else
        std::cout << "Not deleted/not found" << std::endl;
    
    
    badHashQP1->printTable();
    
    
    
    
    return 0;
}