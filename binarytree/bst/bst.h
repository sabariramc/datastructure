#include "binarytree.h"

class BST : public BinaryTree
{
protected:
    virtual int test_node(Node *nav);

public:
    bool insert_node(int value);
    virtual bool test_tree_integraty();
};