#include "binarytree.h"

#ifndef BST_H
#define BST_H

class BST : public BinaryTree
{
protected:
    virtual int test_node_value(Node *nav);

public:
    bool insert_node(int value);
    virtual bool test_tree_integraty();
    const int *search(int value);
};

#endif // !BST_H
