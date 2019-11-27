#ifndef LISTNODE_H
#define LISTNODE_H
template <typename T>
class ListNode{
    public:
        T data;
        ListNode<T>* next;
        ListNode<T>* prev;

        //constructor/destructor
        ListNode();
        ListNode(T d);
        ~ListNode();
};
#endif