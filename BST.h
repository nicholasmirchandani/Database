#ifndef BST_H
#define BST_H
#include "TreeNode.cpp"
#include <fstream>
template<typename T>
class BST {
    public:
        TreeNode<T>* root;
        int numItems;

        BST();
        ~BST();

        TreeNode<T>* search(T value);
        void insert(T value);

        //delete
        bool deleteNode(T value);

        //helper function
        void clone(BST<T>* tree);
        bool isEmpty();
        TreeNode<T>* getMin();
        TreeNode<T>* getMax();
        void printTree();
        void printTree(std::ofstream& os);
        void recPrint(TreeNode<T>* node);
        void recPrint(TreeNode<T>* node, std::ofstream& os);
        void recInsert(TreeNode<T>* node);
        void recDelete(TreeNode<T>* node);
        TreeNode<T>* getSuccessor(TreeNode<T>* d) ;
};
#endif