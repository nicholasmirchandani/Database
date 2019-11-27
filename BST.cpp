/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 5: Database

BST.cpp is the template implementation for a Binary Search Tree.
*/
#include "BST.h"
#include <iostream>

/*
    Default Constructor: Initializes empty tree
*/
template<typename T>
BST<T>::BST() {
    root = nullptr; //empty tree
    numItems = 0;
}

/*
    Destructor: Deletes all nodes in the tree
*/
template<typename T>
BST<T>::~BST() {
    //Iterate through tree and delete all children similarly to how recursive print does, using a stack to store parents similar to DFS
    if(root != nullptr) {
        recDelete(root);
    }
}

/*
    Clones a tree into an empty tree
    treeToClone: Tree to be cloned
*/
template<typename T>
void BST<T>::clone(BST<T>* treeToClone) {
    if(root != nullptr) {
        recDelete(root);
    }
    if(treeToClone->root != nullptr) {
        recInsert(treeToClone->root);
    }
}


/*
    Recursively inserts node and all of its children into this tree, creating a deep copy
    node: root node of subtree to be inserted
*/
template<typename T>
void BST<T>::recInsert(TreeNode<T>* node) {
    insert(node->key);
    if(node->left != nullptr) {
        recInsert(node->left);
    }
    if(node->right != nullptr) {
        recInsert(node->right);
    }
}

/*
    Recursively deletes node and all children
    node: root node of subtree to be deleted
*/
template<typename T>
void BST<T>::recDelete(TreeNode<T>* node) {
    if(node->left != nullptr) {
        recDelete(node->left);
    }
    if(node->right != nullptr) {
        recDelete(node->right);
    }
    delete(node);
}

/*
    Recursively prints all nodes in the tree inorder
    node: root node of the tree
*/
template<typename T>
void BST<T>::recPrint(TreeNode<T>* node) {
    if(node == nullptr) {
        return;
    }

    //inorder
    recPrint(node->left);
    std::cout << node->key << std::endl; //Value to be printed in this case is the key
    recPrint(node->right);
}

/*
    Recursively prints all nodes in the tree inorder to file
    node: root node of the tree
*/
template<typename T>
void BST<T>::recPrint(TreeNode<T>* node, std::ofstream& os) {
    if(node == nullptr) {
        return;
    }

    //Not inorder to preserve logarithmic behavior of tree when being read in
    os << node->key << std::endl; //Value to be printed in this case is the key
    recPrint(node->left, os);
    recPrint(node->right, os);
}

/*
    Prints the entire tree
*/
template<typename T>
void BST<T>::printTree() {
    recPrint(root);
}

/*
    Prints the entire tree to a file
*/
template<typename T>
void BST<T>::printTree(std::ofstream& os) {
    recPrint(root, os);
}

/*
    Returns maximum value in the tree
*/
template<typename T>
TreeNode<T>* BST<T>::getMax() {
    //Traverse all the way right
    TreeNode<T>* current = root;

    if(root == nullptr) { //Empty tree
        return nullptr;
    }

    while(current->right != nullptr) {
        current = current->right;
    }
    return current;
}

/*
    Returns minimum value in the tree
*/
template<typename T>
TreeNode<T>* BST<T>::getMin() {
    //Traverse all the way left
    TreeNode<T>* current = root;

    if(root == nullptr) { //Empty tree
        return nullptr;
    }

    while(current->left != nullptr) {
        current = current->left;
    }
    return current;
}

/*
    Checks if the tree is empty
    Returns true if the tree is empty, false otherwise
*/
template<typename T>
bool BST<T>::isEmpty() {
    return root == nullptr;
}

/*
    Inserts a node into the tree
    value: Data to be stored within a node of the tree
*/
template<typename T>
void BST<T>::insert(T value) {
    ++numItems;
    TreeNode<T>* node = new TreeNode<T>(value);
    if(root == nullptr) {
        //empty tree
        root = node;
    } else {
        //Tree isnot empty, need to find the insertion location
        TreeNode<T>* current = root;
        TreeNode<T>* parent = nullptr;
        while(true) {
            parent = current;
            if(value < current->key) {
                current = current->left;
                //going left
                if(current == nullptr) {
                    //Found insertion point
                    parent->left = node;
                    break;
                }
            } else if (value > current->key) {
                current = current->right;
                //going right
                if(current == nullptr) {
                    //found insertion point
                    parent->right = node;
                    break;
                }
            }
        }
    }
}

/*
    Returns a TreeNode<T>* to the node if it exists in the tree, nullptr otherwise
*/
template<typename T>
TreeNode<T>* BST<T>::search(T value) {
    if(root == nullptr) {//Empty tree
        return nullptr;
    } else {
        //Tree is not empty
        TreeNode<T>* current = root;
        while(current->key != value) {
            if(value < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
            if(current == nullptr) {
                //did not find the value
                return nullptr;
            }
        }
        //current is the node we were looking for
        return current;
    }
}

/*
    Deletes a node from the tree
    value: data of the node to be deleted
    Returns false if node could not be found in the tree, true otherwise
*/
template<typename T>
bool BST<T>::deleteNode(T value) {
    if(root == nullptr) {
        return false;
    }

    TreeNode<T>* current = root;
    TreeNode<T>* parent = root;
    bool isLeft = true;

    //now let's look for the node
    while(current->key != value) {
        parent = current;
        if(value < current->key) {
            isLeft = true;
            current = current->left;
        } else {
            isLeft = false;
            current = current->right;
        }
        if(current == NULL) {
            //Did not find the value
            return false;
        }
    }

    //we found what we are looking for
    //check is node to be deleted is a leaf node
    if(current->left == nullptr && current->right == nullptr) {
        if(current == root) {
            root = nullptr;
        } else if(isLeft) {
            parent->left = nullptr;
        } else {
            parent -> right = nullptr;
        }
    }
    //node to be deleted has one child, we need to determine if child is left or right and proceed
    else if(current->right == nullptr) {//does'nt have right child must be a left child
        //need to check if node is root
        if(current == root) {
            root = current->left;
        } else if(isLeft) {
            parent->left = current->left;
        } else {
            //right child
            parent->right = current->left;
        }
    }

    //Right child
    else if(current->left == nullptr) {//does'nt have left child must be a right child
        //need to check if node is root
        if(current == root) {
            root = current->right;
        } else if(isLeft) {
            parent->left = current->right;
        } else {
            //right child
            parent->right = current->right;
        }
    } else {
        //Node to be deleted has 2 children, and let the games begin
        TreeNode<T>* successor = getSuccessor(current);
        if(current == root) {
            root = successor;
        } else if (isLeft) {
            parent->left = successor;
        } else {
            parent->right = successor;
        }
        successor->left = current->left;
    }
    //Delete current at some point in the method since it's dynamically allocated
    delete(current);
    --numItems;
    return true;
}

/*
    Obtains successor for a node to be deleted
    d: Node to which to obtain the successor
    Returns successor of given node
*/
template<typename T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* d) {  //d is the node to be deleted
    TreeNode<T>* current = d->right;
    TreeNode<T>* sp = d;   //sp - successor's parent
    TreeNode<T>* successor = d;

    while(current != NULL) {
        //traverse tree until we find the successor
        sp = successor;
        successor = current;
        current = current->left;
    }

    //by this point, all of our pointers should be in the right spot

    if(successor != d->right) {
        sp->left = successor->right;    //isolating the successor to move it back to the tree; not moving the whole subtree to preserve logarithmic behavior
        successor->right = d->right;
    }

    return successor;
}