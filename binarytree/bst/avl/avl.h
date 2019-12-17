#include "bst.h"

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
    void check_tree_balance(AVLNode **nav);
    void rotation_left_left(AVLNode **nav);
    void rotation_left_right(AVLNode **nav);
    void rotation_right_left(AVLNode **nav);
    void rotation_right_right(AVLNode **nav);

public:
    bool insert_node(int value);
    bool delete_node(int value);
};
