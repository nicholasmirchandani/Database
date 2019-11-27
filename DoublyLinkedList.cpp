/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 5: Database

DoublyLinkedList.cpp is the template implementation for a Doubly Linked List.
*/

#include <iostream>
#include "DoublyLinkedList.h"

/*
    Default Constructor: initializes values as needed
*/
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    size = 0;
    front = nullptr;
    back = nullptr;
}

/*
    Destructor: Removes all nodes from a list when destroying it, to ensure that all memory is given back to the OS.
*/
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while(!isEmpty()) {
        removeFront();
    }
}

/*
    Inserts a node to the front of the linked list.
    d: data to be inserted into the front of the linked list.
*/
template <typename T>
void DoublyLinkedList<T>::insertFront(T d) {
    ListNode<T>* node = new ListNode<T>(d);
    if(isEmpty()) { // size == 0
        //We have an empty list
        back = node;
    } else {
        //not an empty list
        node->next = front;
        front->prev = node;
    }
    front = node;
    ++size;
}

/*
    Removes the front node from the linked list
    Returns data of node removed
*/
template <typename T>
T DoublyLinkedList<T>::removeFront() {
    //check if empty
    if(isEmpty()) {
        throw DoublyLinkedListException::LIST_EMPTY;
    }

    ListNode<T>* ft = front;

    if(front->next == nullptr) {
        //Only one element in the list
        back = nullptr;
    } else {
        front->next->prev = nullptr;
        front = nullptr;
    }
    front = ft->next;   //Changed front->next to ft->next since front might be nullptr here
    T temp = ft->data;
    --size;
    ft->next = nullptr;
    delete ft;
    return temp;
}

/*
    Inserts a node into the back of the linked list
    d: data to be inserted into the back of the linked list
*/
template <typename T>
void DoublyLinkedList<T>::insertBack(T d) {
    ListNode<T>* node = new ListNode<T>(d);

    if(isEmpty()) { //size == 0 
        //we have an empty list
        front = node;
    } else {
        //not an empty list
        back->next = node;
        node->prev = back;
    }
    back = node;
    ++size;
}

/*
    Removes node from the back of the linked list
    Returns node removed
*/
template <typename T>
T DoublyLinkedList<T>::removeBack() {
    if(isEmpty()) {
        throw DoublyLinkedListException::LIST_EMPTY;
    }

    ListNode<T>* bk = back;
    
    if(front->next == nullptr) { //Only one element in the list
        front = nullptr;
    } else {
        back->prev->next = nullptr;
        back = nullptr;
    }
    back = bk->prev; //Changed back->prev to bk->prev since back may be nullptr here
    T temp = bk->data;
    --size;
    bk->prev = nullptr;
    delete bk;
    return temp;
}

/*
    Removes a node based on data stored.
    d: Data to search for in the linked list; if found, it will remove the node.
    Returns pointer to node removed from the linked list.
*/
template <typename T>
ListNode<T>* DoublyLinkedList<T>::remove(T d) { //aka int key
    //check if empty before attempting to remove a node

    ListNode<T>* curr = front;

    while(curr->data != d) {
        curr = curr->next;

        if(curr == nullptr) {//Value does not exist in list
            return nullptr;
        }
    }
    //If we get to this point, we found the value/node to be removed
    return removeNode(curr);
}

/*
    Removes a node at a given position of a linked list.
    pos: position at which to remove a node
    Returns data held in node removed
*/
template <typename T>
T DoublyLinkedList<T>::removeAt(int pos) {
    if(pos >= size) {
        throw DoublyLinkedListException::INVALID_INDEX; //Index too large
    }

    if(pos < 0) {
        throw DoublyLinkedListException::INVALID_INDEX; //Index too small
    }
    ListNode<T>* curr = front;
    for(int i = 0; i < pos; ++i) {
        curr = curr->next;
    }
    //Now we've found the node we want to remove: curr
    return removeNode(curr)->data;
}

/*
    Checks if the list is empty
    Returns true if the list is empty, false otherwise
*/
template <typename T>
bool DoublyLinkedList<T>::isEmpty() {
    return front == nullptr;
}

/*
    Prints the contents of the linked list.
*/
template <typename T>
void DoublyLinkedList<T>::printList() const{
    ListNode<T>* curr = front;
    std::cout << "{ ";
    while(curr != nullptr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << "}" << std::endl;
}

/*
    Prints the contents of the linked list to a file.
*/
template <typename T>
void DoublyLinkedList<T>::printList(std::ostream& os) const{
    ListNode<T>* curr = front;
    os << "{ ";
    while(curr != nullptr) {
        os << curr->data << " ";
        curr = curr->next;
    }
    os << "}" << std::endl;
}

/*
    Removes a specific node from the linked list.  Used internally due to code reusability.
    curr: node to be removed
    Returns pointer to node removed
*/
template <typename T>
ListNode<T>* DoublyLinkedList<T>::removeNode(ListNode<T>* curr) {
    if(curr == front) {
        front = curr->next;
    } else {
        //It's not the front, it's somewhere in between
        curr->prev->next = curr->next;
    }

    if(curr == back) {
        back = curr->prev;
    } else {
        //It's not the back, it's somewhere in between
        curr->next->prev = curr->prev;
    }

    curr->next = nullptr;
    curr->prev = nullptr;

    --size;
    return curr;
}

template <typename T>
unsigned int DoublyLinkedList<T>::getSize() {
    return size;
}