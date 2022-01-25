//Weston Cox
//Name Generator / Hash Table / Binary Search Tree Demo
//01-19-2022

// This program reads names in from two files and creates a hash table with chained collision resolution for the names.
// The sample names are first and last names from Chippenham, Wiltshire in the UK from the 1841 census
// I got the census data from this very neat website:
//      https://www.freecen.org.uk/freecen2_contents?locale=en


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "nameHashTable.h"
#include "BST.h"
using namespace std;

////HELPER FUNCTION PROTOTYPES
void populateTable(string inputFile, nameHashTable &table);
void fillVector(string inputFile, vector<string>& outputVector);
void bstBasicInfo(BST<string> &stringTree);
void bstTraversals(BST<string> &stringTree);
void tableStatPrint(nameHashTable &inTable);
void wordAnalysisHeader();

////MAIN PROGRAM
int main() {
    //This variable can be switched off to quit the program after the mainLoop is complete
    bool mainLoop = true;
    //This variable is used to store user input
    string menuChoice = "false";
    //This variable is used with getline to take sizes in as strings
    string numChoiceString;
    //This is used to convert user size inputs into integers
    int numChoice;
    //This value determines how many sample names will be printed after shuffling
    const int VEC_PRINT_COUNT = 10;
    //Size of first Hash Table
    const int HT_SIZE_1 = 500;
    //Size of second Hash Table
    const int HT_SIZE_2 = 3000;

    while(mainLoop){

        //// 0. Welcome Message
        cout << "Welcome to the Data Structure Sample program!" << endl;
        cout << "This program will demonstrate some features of" << endl;
        cout << "hash tables and binary search trees using names" << endl;
        cout << "drawn from 1841 census data from Chippenham, Wiltshire" << endl;
        cout << "in the UK. Our hash tables use chained collision resolution, " << endl;
        cout << "meaning each 'index' of the hash table is a singly linked list" << endl;
        cout << "where new elements are appended on to the list when an index is occupied." << endl;
        cout << "When prompted to press any key, press ENTER to continue the program." << endl;
        system("pause");

        //// 1.Initialize Tables and BSTs
        nameHashTable fNameTable(HT_SIZE_1);
        nameHashTable lNameTable(HT_SIZE_2);
        BST<string> fNameBST;
        BST<string> lNameBST;
        BST<string> miniBST;
        cout << "Hash Tables and BSTs Initialized. Shuffling...." << endl;

        ////2. Read Names and Shuffle Vectors
        vector<string> fNameVector;
        vector<string> lNameVector;
        unsigned num = chrono::system_clock::now().time_since_epoch().count();
        fillVector("../fNames_UK_1841", fNameVector);
        fillVector("../lNames_UK_1841", lNameVector);
        shuffle(fNameVector.begin(), fNameVector.end(), default_random_engine(num));
        shuffle(lNameVector.begin(), lNameVector.end(), default_random_engine(num));

        ////3.Print Sample
        cout << "Inputs shuffled.... " << endl;
        system("pause");
        cout << "Printing " << VEC_PRINT_COUNT << " results from each vector: " << endl;
        for (int j = 0; j < VEC_PRINT_COUNT; j++){
            cout << setw(16) << left << fNameVector[j] << " " << lNameVector[j] << endl;
        }

        ////4.Fill First Names
        for (int j = 0; j < fNameVector.size(); j++) {
            fNameTable.addWord(fNameVector[j]);
            fNameBST.insert(fNameVector[j]);
        }

        ////5.Fill Last Names
        for (int j = 0; j < lNameVector.size(); j++){
            lNameTable.addWord(lNameVector[j]);
            lNameBST.insert(lNameVector[j]);
        }

        ////6.Fill Mini Printable BST
        //IMPORTANT: Avoid duplicate inputs
        for (int j = 0; j < VEC_PRINT_COUNT / 2; j++){
            if (!miniBST.contains(fNameVector[j])){
                miniBST.insert(fNameVector[j]);
            }
            if (!miniBST.contains(lNameVector[j])){
                miniBST.insert(lNameVector[j]);
            }

        }

        ////7. Print Hash Table Info
        cout << "Now we're ready to examine our objects. Press enter" << endl;
        system("pause");

        cout << "FIRST NAME HASH TABLE: SIZE " << HT_SIZE_1 << endl;
        //wordAnalysisHeader();
        tableStatPrint(fNameTable);
        cout << endl;
        cout << "Here's a visual representation of the linked lists stored in each" << endl;
        cout << "index of our Hash Table..." << endl;
        system("pause");
        fNameTable.listInfo();
        system("pause");


        cout << "LAST NAME HASH TABLE SIZE: " << HT_SIZE_2 << endl;
        //wordAnalysisHeader();
        tableStatPrint(lNameTable);
        cout << endl;
        cout << "Here's a visual representation of the linked lists stored in each" << endl;
        cout << "index of our Hash Table..." << endl;
        system("pause");
        lNameTable.listInfo();

        cout << endl << endl << "*****************************************" << endl << endl;
        cout << "You can see how in the first names example, every index has" << endl;
        cout << "names in it, because the capacity is smaller than the number" << endl;
        cout << "of unique names. Not so for our last names, which had a larger" << endl;
        cout << "capacity. However, there were still many indices with more than" << endl;
        cout << "one entry, because those words still have the same hash value." << endl;
        cout << endl << endl << "*****************************************" << endl << endl;

        ////8.Print BST Info
        cout << "Now let's look at our BSTs...." << endl;
        system("pause");
        cout << "FIRST NAME BINARY SEARCH TREE" << endl;
        bstBasicInfo(fNameBST);
        system("pause");
        cout << "LAST NAME BINARY SEARCH TREE" << endl;
        bstBasicInfo(lNameBST);
        system("pause");
        cout << "MINI TREE" << endl;
        bstBasicInfo(miniBST);
        bstTraversals(miniBST);



        //// Ask User Whether To Repeat
        cout << "Would you like to go again? (Y/N) ";
        getline(cin, menuChoice);
        if(menuChoice == "Y" || menuChoice == "y") mainLoop = true;
        else mainLoop = false;
    }
    cout << "Thanks!";
    return 0;
}

////HELPER FUNCTION IMPLEMENTATIONS
void populateTable(string fileName, nameHashTable &table){
    //1.OPEN FILE
    ifstream inFile;
    string tableCapString;
    string tempString;

    inFile.open(fileName);
    if (!inFile) cout << "Error! Could not open " << fileName << endl;

    //2B.FILL TABLE
    while (inFile >> tempString){
        //tempString = cleanWord(tempString);
        table.addWord(tempString);
    }
    inFile.close();

}

void fillVector(string inputFileName, vector<string>& outputVector){
    //1.OPEN FILE
    ifstream inFile;
    string tableCapString;
    string tempString;

    inFile.open(inputFileName);
    if (!inFile) cout << "Error! Could not open " << inputFileName << endl;

    //2B.FILL TABLE
    while (inFile >> tempString){
        //tempString = cleanWord(tempString);
        outputVector.push_back(tempString);
    }
    inFile.close();

}

void bstBasicInfo(BST<string> &stringTree){
    cout << "# of Nodes: " << stringTree.size() << endl;
    cout << "# of Leaves: " << stringTree.getLeafCount() << endl;
    cout << "BST Height: " << stringTree.getHeight() << endl;
    cout << "BST Empty? " << stringTree.isEmpty() << endl << endl;
}

void bstTraversals(BST<string> &stringTree){
    cout << "Pre-order: " <<  stringTree.displayPreOrder() << endl;
    cout << "In-order: " << stringTree.displayInOrder() << endl;
    cout << "Post-Order: " << stringTree.displayPostOrder() << endl << endl;
}

void tableStatPrint(nameHashTable &inTable){
    double loadFactor = static_cast<double>(inTable.getUniqueWordCount()) / static_cast<double>(inTable.getCapacity());
    cout << "Hash Table Statistics: " << endl;
    cout << "# Unique    # Total     Load F. " << endl;
    cout << "+---------+------------+-----------+" << endl;
    cout << setw(8) << left << inTable.getUniqueWordCount() << "  |  " << setw(8) << inTable.getTotalWordCount()
         << "  |  " << setw(8) << loadFactor << endl;
}

void wordAnalysisHeader(){
    cout << "Analysis: " << endl;
    cout << "    Word                  Count     " << endl;
    cout << "+----------------------+-----------+" << endl;
}
