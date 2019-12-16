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
            balance_factor = 0;
            left_height = 0;
            right_height = 0;
        }
    };
    bool delete_node(Node **temp, int value);
    void insert_node(AVLNode **nav, int value);
    void check_tree_balance(AVLNode **nav);
    void rotation_left_left(AVLNode **nav);
    void rotation_left_right(AVLNode **nav);
    void rotation_right_left(AVLNode **nav);
    void rotation_right_right(AVLNode **nav);

public:
    using BST::delete_node;
    void insert_node(int value);
};
