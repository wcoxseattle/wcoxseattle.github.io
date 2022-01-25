//Weston Cox
//nameHashTable Header File
//01-19-2022

#ifndef DATASTRUCTURESAMPLE_NAMEHASHTABLE_H
#define DATASTRUCTURESAMPLE_NAMEHASHTABLE_H
#include <string>
#include <algorithm>
using namespace std;

//Author: Weston Cox
//Filename: nameHashTable.h
//Version: 1.0
//Description: The nameHashTable takes a string, finds its hash code and stores it
//    in a location dependent on its hash code and table size. It uses chained collision
//    resolution, meaning each index is a singly linked list with new elements being
//    appended. The list stores "buckets" which contain a string and a count for that
//    element.

class nameHashTable {
private:
    //CLASS INVARIANT: Strings are put into "buckets" which contain the word, a count,
    //    and a pointer to the next "bucket" in the list. A nameHashTable has a
    //    dynamically allocated array of "buckets", and also tracks the capacity,
    //    number of unique words, and total number of words added.

    //The Bucket stores a word, its count, and a pointer to the next Bucket
    struct Bucket {
        string word = "";
        int wordCount = 0;
        Bucket* next = nullptr;
        //const Bucket* operator=(Bucket& rhs);
    };
    //The number of indices in the hash table
    int capacity;
    //A dynamically allocated array of buckets
    Bucket** wordList;
    //Number of unique words entered into the hash table
    int uniqueCount;
    //Total words, including duplicate
    int totalCount;

////PRIVATE METHODS
    //Calculates the hash value, or target index of a word
    int getIndex(string input);
    //Deletes a bucket
    void deleteBucket(Bucket*& input);
    //Recursive helper for addWord
    int addWord(Bucket*& ptr, Bucket*& newBucket);
    //Recursive helper for removeWord
    void removeWord(Bucket*& ptr, string input);
    //Recursive helper for getWordCount
    int getWordCount(string input, Bucket*& ptr);

public:
    ////CONSTRUCTOR AND DESTRUCTOR
    nameHashTable(int capacityIn);
    ~nameHashTable();
    const nameHashTable operator=(nameHashTable&);

    ////PUBLIC METHODS
    //Adds a word to the hash table
    int addWord(string input);
    //Removes a word from the hash table
    void removeWord(string input);
    //Returns the number of times a word has been added
    int getWordCount(string input);
    //Returns the capacity, or number of indices
    int getCapacity();
    //Returns the number of unique words
    int getUniqueWordCount();
    //Returns the number of words, counting duplicates
    int getTotalWordCount();
    //Checks if the hash table is empty
    bool empty();
    //Prints the contents of all indices
    void listInfo();

};


#endif //DATASTRUCTURESAMPLE_NAMEHASHTABLE_H
