//Weston Cox
//Binary Search Tree Header AND Implementation
//01-25-2022

//Author: Weston Cox
//Filename: BST.h
//Version: 1.0
//Description: The BST (Binary Search Tree) is a template class that creates a
//    BST based on input determined at creation (string, int, etc). Each node
//    contains data, and has a left and right child. Each time a node is added,
//    it will append to the left child if its data is less than the existing node,
//    or to the right child if its data is equal or greater.
//PRECONDITION: This BST structure assumes NO DUPLICATE INPUTS. It will still create
//    the tree just fine with duplicates, but some of the functions will return
//    unexpected results, e.g. finding the level of only the FIRST occurance of a word

#ifndef DATASTRUCTURESAMPLE_BST_H
#define DATASTRUCTURESAMPLE_BST_H
#include <iostream>
#include <sstream>
#include <string>
#include <sstream>
using namespace std;

//CLASS INVARIANT: Nodes contain data, and pointers to left and right children. New nodes append
//    to the left if incoming data is LESS than the existing, or to the right if GREATER OR EQUAL

template <typename T>
class BST {
private:
    struct Node {
        T data;
        Node * left;
        Node * right;
    };
    Node * root;

    //Copies a BST
    void copyTree(const BST);
    //Recursive helper for BST copy
    void copyTree(Node*&, const Node*);
    //Recursive helper for insert
    void insert(Node *&, Node *&);
    //Recursive helper for remove
    void remove(Node *&, T);
    //Recursive helper for destructor
    void makeDeletion(Node *&, T);
    //Destroys a whole tree
    void destroyTree(Node *&);
    //Recursive helper for Preorder traversal
    void displayPreOrder(Node*, stringstream&);
    //Recursive helper for Inorder traversal
    void displayInOrder(Node*, stringstream&);
    //Recursive helper for Postorder traversal
    void displayPostOrder(Node*, stringstream&);
    //Recursive helper for finding leaf count
    void getLeafCount(Node*, int&);
    //Recursive helper for finding the BST's height
    int getHeight(Node*);
    //Recursive helper for finding the level of a given word
    void getLevel(Node*, T, int&);
    //Recursive helper for listing all ancestors of a given word
    void getAncestors(Node*, T, stringstream&);
    //Recursive helper for finding BST size
    void size(Node*, int&);


    //Extra or Modified Methods for P2
public:
    //Constructor
    BST();
    //Copy constructor
    BST(const BST&);
    //Destructor
    ~BST();
    //Overloaded =
    BST<T>& operator=(const BST&);
    //Returns true if data T exists in BST
    bool contains(T);
    //Adds node with data T
    void insert(T);
    //Removes node with data T
    //PRECONDITION: Avoid duplicate inputs BEFORE inserting a node
    void remove(T);

    //Returns Preorder traversal - Root/Left/Right
    string displayPreOrder();
    //Returns Inorder traversal - Left/Root/Right
    string displayInOrder();
    //Returns Postorder traversal - Left/Right/Root
    string displayPostOrder();

    //Returns true if the BST is empty
    bool isEmpty();
    //Returns the size of the BST
    int size();
    //Returns the number of nodes with no children
    int getLeafCount();
    //Returns the height of the tree
    int getHeight();
    //Returns the level of a node with data T
    int getLevel(T);
    //Returns ancestors for a node with data T
    string getAncestors(T);
};


//////////////////////////////////////////////////////////
//                  IMPLEMENTATION                      //
//////////////////////////////////////////////////////////

////  CONSTRUCTOR AND DESTRUCTOR/////////////////////////
//Constructor
template <typename T>
BST<T>::BST() {
    root = nullptr;
    //nodeCount = 0;
}
//Destructor
template <typename T>
BST<T>::~BST() {
    destroyTree(root);
}
//Copy constructor
template <typename T>
BST<T>::BST(const BST<T> &thatTree){
    root = nullptr;
    copyTree(thatTree.root);
}

////  PUBLIC METHODS/////////////////////////////////////
//Overloaded = operator
template <typename T>
BST<T>& BST<T>::operator=(const BST<T> &thatTree) {
    if (this != &thatTree){

        destroyTree(root);
        copyTree(thatTree->root);
        return *this;
    }

}
//Copies a tree
template <typename T>
void BST<T>::copyTree(Node* &thisTree, const Node* thatTree){

    if (thisTree != nullptr) {
        //create new node
        //set thisTree->value = thatTree->value
        //thisTree.insert(thatTree.ptr->data);
        thisTree->data = thatTree->data;
        thisTree->left = nullptr;
        thisTree->right = nullptr;
        //Set new node's left and right to null
        copyTree(thisTree->left, thatTree->right);
        copyTree(thisTree->left, thatTree->right);
    }
}
//Returns true if item T exists in the BST
template <typename T>
bool BST<T>::contains(T item) {
    Node * ptr = root;
    while (ptr != nullptr) {
        if (ptr->data == item)
            return true;
        else if (ptr->data > item)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    return false;
}
//Inserts item T into the tree
//PRECONDITION: Avoid duplicate items
template <typename T>
void BST<T>::insert(T item) {
    Node * newNode = new Node;
    //nodeCount++;
    newNode->data = item;
    newNode->left = newNode->right = nullptr;

    insert(root, newNode);
}
//Recursive helper for insert
//POSTCONDITION: Iterates through existing nodes, moving to a node's left child
//    if input is smaller, or the node's right child if input is greater
template <typename T>
void BST<T>::insert(Node *& ptr, Node *& newNode) {
    if (ptr == nullptr)
        ptr = newNode;
    else if (ptr->data > newNode->data){
        insert(ptr->left, newNode);
        //FOR DEBUGGING
        //cout << "Went left..." << endl;
    }
    else{
        insert(ptr->right, newNode);
        //FOR DEBUGGING
        //cout << "Went right..." << endl;
    }
}
//Removes a node containing item T
//PRECONDITION: This won't work properly if duplicate input has been added
template <typename T>
void BST<T>::remove(T item) {
    if (contains(item))
        remove(root, item);
}
//Helper function for remove. Finds item, then deletes it
template <typename T>
void BST<T>::remove(Node *& ptr, T item) {
    if (ptr != nullptr) {
        if (ptr->data > item)
            remove(ptr->left, item);
        else if (ptr->data < item)
            remove(ptr->right, item);
        else
            makeDeletion(ptr, item);
    }
}
//Destroys an entire tree
template <typename T>
void BST<T>::destroyTree(Node *&ptr) {
    if (ptr != nullptr) {
        destroyTree(ptr->left);
        destroyTree(ptr->right);
        delete ptr;
    }
    ptr = nullptr;
}
//Removes a node from the tree, and accounts for the node's children if any
template <typename T>
void BST<T>::makeDeletion(Node *& ptr, T item) {
    Node * curr = nullptr;
    if (ptr != nullptr) {
        if (ptr->left == nullptr) {
            curr = ptr;
            ptr = ptr->right;
            delete curr;
            //nodeCount--;
        } else if (ptr->right == nullptr) {
            curr = ptr;
            ptr = ptr->left;
            delete curr;
            //nodeCount--;
        } else {
            curr = ptr->right;
            while (curr->left != nullptr)
                curr = curr->left;
            ptr->data = curr->data;
            remove(ptr->right, curr->data);
        }
    }
}
//Returns true if no nodes exist
template <typename T>
bool BST<T>::isEmpty()
{
    if (root == nullptr) return true;
    else return false;
}
//Returns the number of nodes in the tree
template <typename T>
int BST<T>::size() {
    int counter = 0;
    size(root, counter);
    return counter;
}
//Recursive helper for size
template <typename T>
void BST<T>::size(Node* ptr, int& counter) {
    if (ptr != nullptr) {
        counter++;
        size(ptr->left, counter);
        size(ptr->right, counter);
    }
}
//Returns the count of leaves, which are nodes with NO children
template <typename T>
int BST<T>::getLeafCount() {
    int count = 0;
    getLeafCount(root, count);
    return count;

}
//Recursive helper for getLeafCount
template <typename T>
void BST<T>::getLeafCount(Node *ptr, int &count) {
    if (ptr != nullptr) {

        if (ptr->left == nullptr && ptr->right == nullptr) count ++;
        getLeafCount(ptr->left, count);
        getLeafCount(ptr->right, count);
    }
}
//Returns the height of the BST
template <typename T>
int BST<T>::getHeight() {
    int tempHeight = 0;
    if (!isEmpty())
    {
        tempHeight = getHeight(root);
    }
    return tempHeight;
}
//Recursive helper for getHeight
template <typename T>
int BST<T>::getHeight(Node* ptr){
    int h = 0;
    if (ptr != nullptr) {
        if (ptr->right == nullptr && ptr->left == nullptr) return 0;
        //else if (ptr->right != nullptr && ptr->left != nullptr) {
        else if (ptr->right != nullptr || ptr->left != nullptr) {
            h = max(getHeight(ptr->left), getHeight(ptr->right));
        }
    }
    return 1 + h;
}
//Returns the level of a node containing data T
template <typename T>
int BST<T>::getLevel(T input){
    int level = 0;
    if (!contains(input)) return -1;
    if (!isEmpty()){
        getLevel(root, input, level);
    }
    return level;
}
//Recursive helper for getLevel()
template <typename T>
void BST<T>::getLevel(Node* ptr, T input, int& l){
    if (ptr != nullptr){
        if (ptr->data == input){
            //FOR DEBUGGING
            //cout << "Found " << input << " at level " << l << endl;
        }
        else {
            l++;
            if (ptr->data > input){
                getLevel(ptr->left, input, l);
                //cout << input << " Went left... l = " << l << endl;
            }
            else if (ptr->data < input){
                getLevel(ptr->right, input, l);
                //cout << input << " Went right... l = " << l << endl;
            }
        }
    }
}
//Lists all ancestors of node with data T
template <typename T>
string BST<T>::getAncestors(T input){
    string ancestors = "";
    stringstream ss;
    if (!contains(input)) return "getAncestors input not found...";
    if (!isEmpty()){
        getAncestors(root, input, ss);
    }
    ancestors = ss.str();
    return ancestors;
}
//Recursive helper for getAncestors()
template <typename T>
void BST<T>::getAncestors(Node* ptr, T input, stringstream& ss){
    if (ptr != nullptr){
        if (ptr->data == input){
            //FOR DEBUGGING
            //cout << "Found " << input << " at level " << l << endl;
        }
        else {
            if (ptr->data > input){
                getAncestors(ptr->left, input, ss);
                ss << ptr->data << " ";
            }
            else if (ptr->data < input){
                getAncestors(ptr->right, input, ss);
                ss << ptr->data << " ";
            }
        }
    }
}
////  PRIVATE METHODS/////////////////////////////////////


//  TRAVERSALS////////////////////////////////////////////
//Lists Preorder traversal - Node/Left/Right
template <typename T>
string BST<T>::displayPreOrder() {
    string result;
    stringstream runningString;
    displayPreOrder(root, runningString);
    result = runningString.str();
    return result;
}
//Recursive helper for preorder
template <typename T>
void BST<T>::displayPreOrder(Node * ptr, stringstream& runningString) {
    if (ptr != nullptr) {
        runningString << ptr->data << " ";
        //FOR DEBUGGING
        //cout << result << endl;

        displayPreOrder(ptr->left, runningString);
        //FOR DEBUGGING
        //cout << "Preorder left... " << endl;

        displayPreOrder(ptr->right, runningString);
        //FOR DEBUGGING
        //cout << "Preorder right...." << endl;
    }
}
//Lists Inorder traversal - Left/Node/Right
template <typename T>
string BST<T>::displayInOrder() {
    string result;
    stringstream runningString;
    displayInOrder(root, runningString);
    result = runningString.str();
    return result;

}
//Recursive helper for Inorder
template <typename T>
void BST<T>::displayInOrder(Node * ptr, stringstream &runningString) {
    if (ptr != nullptr) {
        displayInOrder(ptr->left, runningString);
        runningString << ptr->data << " ";
        displayInOrder(ptr->right, runningString);
    }
}
//Lists Postorder traversal - Left/Right/Node
template <typename T>
string BST<T>::displayPostOrder() {
    string result = "";
    stringstream runningString;
    displayPostOrder(root, runningString);
    result = runningString.str();
    return result;
}
//Recursive helper for postorder
template <typename T>
void BST<T>::displayPostOrder(Node * ptr, stringstream &runningString) {
    if (ptr != nullptr) {

        displayPostOrder(ptr->left, runningString);

        displayPostOrder(ptr->right, runningString);

        runningString << ptr->data << " ";
    }
}
#endif //DATASTRUCTURESAMPLE_BST_H
