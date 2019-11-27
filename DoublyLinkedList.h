#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include "ListNode.cpp" //Including cpp instead of h because templates

enum DoublyLinkedListException {
    LIST_EMPTY = 1,
    INVALID_INDEX
};

template <typename T>
class DoublyLinkedList {
    private:
        unsigned int size;
        ListNode<T>* removeNode(ListNode<T>* curr); //Used in implementation for code reusability, but should not be needed for use of ADT

    public:
        DoublyLinkedList();
        ~DoublyLinkedList();

        void insertFront(T d);
        void insertBack(T d);
        T removeFront();
        T removeBack();
        ListNode<T>* remove(T d);
        T removeAt(int pos);

        ListNode<T>* front;
        ListNode<T>* back;

        bool isEmpty();
        void printList() const;
        void printList(std::ostream& os) const;
        unsigned int getSize();
};
#endif