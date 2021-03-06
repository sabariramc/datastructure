#include "bst.h"

#ifndef AVL_H
#define AVL_H

class AVL : public BST
{
protected:
    struct AVLNode : Node
    {
        int balance_factor;
        int left_height;
        int right_height;
        AVLNode(int value) : Node(value)
        {
            left_height = 0;
            right_height = 0;
        }
    };
    using BinaryTree::delete_node;
    int insert_node(AVLNode **nav, int value);
    int delete_node(AVLNode **nav, int value);
    int delete_node_by_copying(AVLNode **target, AVLNode **nav);
    void check_height_balance(AVLNode **nav);
    void rotation_left_left(AVLNode **nav);
    void rotation_left_right(AVLNode **nav);
    void rotation_right_left(AVLNode **nav);
    void rotation_right_right(AVLNode **nav);
    void print_node(Node *node);
    int test_node_height(AVLNode *nav);

public:
    bool insert_node(int value);
    bool test_tree_integraty();
    bool delete_node(int value);
};

#endif // !AVL_H
