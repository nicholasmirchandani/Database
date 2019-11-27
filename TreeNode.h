#ifndef TREENODE_H
#define TREENODE_H
template<typename T>
class TreeNode {
    public:
        TreeNode();
        TreeNode(const T& k);    //k=key, which in this example is also the value(data)
        ~TreeNode();        //when creating a template class destructor must be virtual

        T key;
        TreeNode<T>* left;
        TreeNode<T>* right;
};
#endif