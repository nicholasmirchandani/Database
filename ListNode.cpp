/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 5: Database

ListNode.cpp is the implementation of a node of a linked list
*/
#include "ListNode.h"

/*
    Default Constructor: Does nothing, but exists because it's good practice to always have one
*/
template <typename T>
ListNode<T>::ListNode() {
    //Default Constructor
}

/*
    Overloaded Constructor: Creates a listnode based on given data
    d: Data to be stored in the ListNode
*/
template <typename T>
ListNode<T>::ListNode(T d) {
    data = d;
    next = nullptr; //nullptr
    prev = nullptr;
}

/*
    Destructor: nulls out pointers for security reasons
*/
template <typename T>
ListNode<T>::~ListNode() {
    next = nullptr;
    prev = nullptr;
}
