#include "binarytree.h"

#ifndef BST_H
#define BST_H

class BST : public BinaryTree
{

protected:
    using BinaryTree::delete_node;
    virtual bool delete_node(Node **temp, int value);
    virtual int test_node_value(Node *nav);
    virtual Node **search(Node **nav, int value);

public:
    bool insert_node(int value);
    virtual bool test_tree_integraty();
    const int *search(int value);
    bool delete_node(int value);
};

#endif // !BST_H
