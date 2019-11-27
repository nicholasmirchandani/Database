/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 5: Database

ListNode.cpp is the implementation of a node of a BST
*/
#include "TreeNode.h"

/*
    Default Constructor: Initializes key left and right to default values
*/
template<typename T>
TreeNode<T>::TreeNode() {
    //Don't use this :(
    left = nullptr;
    right = nullptr;
}

/*
    Overloaded Constructor: Initializes key to desired values and clears left and right
    k: Desired value of key
*/
template<typename T>
TreeNode<T>::TreeNode(const T& k) { //Passes T by const reference to avoid breaking any affiliated pointers
    key = k;
    left = nullptr;
    right = nullptr;
}

/*
    Destructor: Nulls out values for security reasons
*/
template<typename T>
TreeNode<T>::~TreeNode() {
    //Nulling out pointers for security reasons
    left = nullptr;
    right = nullptr;
}