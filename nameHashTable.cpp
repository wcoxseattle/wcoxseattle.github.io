//Weston Cox
//nameHashTable Implementation File
//01-19-2022

//Author: Weston Cox
//Filename: nameHashTable.cpp
//Version: 1.0
//Description: The nameHashTable takes a string, finds its hash code and stores it
//    in a location dependent on its hash code and table size. It uses chained collision
//    resolution, meaning each index is a singly linked list with new elements being
//    appended. The list stores "buckets" which contain a string and a count for that
//    element.

#include "nameHashTable.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include "nameHashTable.h"

//////////////////////////////////////////////////////////
//                      IMPLEMENTATION                  //
//////////////////////////////////////////////////////////

////          PRIVATE     //////////////////////////////////////
int nameHashTable::getIndex(string input){
    size_t hashCode = hash<string>{}(input);
    int index = hashCode % this->capacity;
    return index;
}

void nameHashTable::deleteBucket(Bucket*& input){
    if (input != nullptr) deleteBucket(input->next);
    delete input;
}

////          PUBLIC      ///////////////////////////////////////
////CONSTRUCTOR AND DESTRUCTOR
//INTERFACE INVARIANT: A nameHashTable takes in a capacityIn integer
//    that determines how many indices the wordList will have
nameHashTable::nameHashTable(int capacityIn) {
    capacity = capacityIn;
    uniqueCount = 0;
    totalCount = 0;
    wordList = new Bucket*[capacityIn];

    //FOR DEBUGGING
    //cout << "nameHashTable part 1.... ";

    //for (int j = 0; j < capacityIn; j++) wordList[j] = new Bucket;
    for (int j = 0; j < capacityIn; j++) wordList[j] = nullptr;

    //FOR DEBUGGING
    //cout << "nameHashTable part 2..." << endl;
}

nameHashTable::~nameHashTable() {

    for (int j = 0; j < capacity; j++){
        Bucket *ptr = wordList[j];
        deleteBucket(ptr);
    }
    delete [] wordList;
    wordList = nullptr;
}

//INTERFACE INVARIANT: Adding a word increases the totalCount, calculates the target
//    index, and then makes a recursive call to the addWord helper function
int nameHashTable::addWord(string input) {
    this->totalCount++;
    int tempIndex = getIndex(input);

    //Bucket *ptr = wordList[tempIndex];
    Bucket* tempBucket = new Bucket;
    tempBucket->word = input;
    tempBucket->wordCount = 1;
    tempBucket->next = nullptr;

    //FOR DEBUGGING
    //cout << "Starting addWord recursions. Total:  " << totalCount << " Adding: " << input << " / " << tempIndex << endl;

    //int result = addWord(ptr, tempBucket);
    int result = addWord(wordList[tempIndex], tempBucket);

    //FOR DEBUGGING
    //cout << endl;

    return result;
}

//INTERFACE INVARIANT: This is the addWord helper function called by its parent.
//    It first checks to see if the target index is empty, occupied by a different
//    word, or already occupied by the incoming word.
//POSTCONDITION: If target index is empty, the bucket is added to that index's root
//    If occupied by a different word, the pointer iterates through the list.
//    If the incoming word is never found, it is appended to the end of the list.
//    If the incoming word exists in the index's linked list, its wordCount is
//    incremented once found
int nameHashTable::addWord(Bucket*& ptr, Bucket*& tempBucket){
    //FOR DEBUGGING
    //cout << "POINTER: " << ptr << endl;

    //CASE 1: Unoccupied
    if (ptr == nullptr){
        //Fill the bucket, update unique word count
        ptr = tempBucket;
        //this->uniqueCount++;
        uniqueCount++;

        //FOR DEBUGGING
        //cout << "F";

        return ptr->wordCount;
    }
        //CASE 2: Occupied
    else if (ptr->word == tempBucket->word) {
        //Update word count for this word if found
        ptr->wordCount++;

        //FOR DEBUGGING
        //cout << ptr << "+" << ptr->word << " = " << ptr->wordCount << endl;

        return ptr->wordCount;
    }
    else if (ptr->next == nullptr){
        ptr->next = tempBucket;
        uniqueCount++;
    }
    else {
        addWord(ptr->next, tempBucket);
    }
    return 0;
}

//INTERFACE INVARIANT: This removes a word from the hash table. It searches for the
//    word, and if found removes it and adjusts the linked list if necessary
void nameHashTable::removeWord(string input){
    int tempIndex = getIndex(input);
//    Bucket* curr = this->wordList[0];
    Bucket* curr = wordList[tempIndex];
    Bucket* prev = curr;
    //Find word by iterating through the list
    while(curr != nullptr) {
        //Update word count for this word if found
        if (curr->word == input) {
            //Decrement unique and total word counts
            uniqueCount--;
            totalCount -= curr->wordCount;
            //Connect entities on either side
            prev->next = curr->next;
            //Delete current entity
            curr = nullptr;
        }
            //Otherwise iterate through the list
        else if (curr->word != input) {
            prev = curr;
            curr = curr->next;
        }

    }
}

//INTERFACE INVARIANT: This function iterates through all entries in the table
//    and returns the sum of the wordCounts. It calls a recursive helper function.
//    It is a more complicated way of getting the total word count, but could be used
//    if you do away with the totalCount variable in the class
int nameHashTable::getWordCount(string input){
    int tempIndex = getIndex(input);
    return getWordCount(input, wordList[tempIndex]);
}

//INTERFACE INVARIANT: This is the helper function for getWordCount. It goes through
//    the linked list in each index, adding up the wordCount for all entries
int nameHashTable::getWordCount(string input, Bucket*& ptr){
    while(ptr != nullptr) {
        //Return word count for this word if found
        if (ptr->word == input){
//            //FOR DEBUGGING
//            cout << "Counted " << ptr->word << " / " << ptr->wordCount << "......" << endl;

            return ptr->wordCount;
        }
            //Otherwise iterate through the list
        else if (ptr->word != input){
//            //FOR DEBUGGING
//            cout << "Wrong word! " << ptr->word << " / " << ptr->wordCount << "......" << endl;
//            cout << "PTR: " << ptr << " TO " << ptr->next << endl;
            return getWordCount(input, ptr->next);
        }
    }
    return 0;
}

//INTERFACE INVARIANT: This returns the nameHashTable's capacity
int nameHashTable::getCapacity(){
    return this->capacity;
}

//INTERFACE INVARIANT: This returns the nameHashTable's uniqueWordCount
int nameHashTable::getUniqueWordCount(){
    return uniqueCount;
}
//INTERFACE INVARIANT: This returns the nameHashTable's totalCount
int nameHashTable::getTotalWordCount(){
    return totalCount;
}
//INTERFACE INVARIANT: This returns true if the nameHashTable is empty
bool nameHashTable::empty(){

    for (int j = 0; j < this->capacity; j++){
        Bucket* ptr = wordList[j];
        if (ptr->next != nullptr){
            return false;
        }
    }
    return true;
}

//INTERFACE INVARIANT: This lists the contents of every index in the nameHashTable.
//    It will provide a lot of lines of output!
void nameHashTable::listInfo(){
    Bucket* ptr;
    //For each bucket, print all words/quantities for non-nullptr values
    for (int j = 0; j < capacity; j++){
        ptr = wordList[j];
        cout << "ID: " << j  << " || ";
        while (ptr!= nullptr){
            cout << setw(16) << left << ptr->word << " " << ptr->wordCount << " | ";
            ptr = ptr->next;
        }
        cout << endl << "------------------------------------------" << endl;
    }
}




