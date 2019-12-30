#include "bst.h"

enum COLOUR
{
    RED,
    BLACK
};

class RedBlack : public BST
{

protected:
    struct RBNode : Node
    {
        enum COLOUR color;
        RBNode *parent;
        RBNode(int value) : Node(value)
        {
            color = RED;
            parent = nullptr;
        }
        ~RBNode()
        {
            parent = nullptr;
        }
    };
    using BinaryTree::delete_node;
    void insert_node(RBNode **nav, RBNode *p, int &value);
    int delete_node(RBNode **nav, int value);
    void insert_fix_up(RBNode **nav);
    void delete_fix_up(RBNode *fix_node, RBNode *fix_node_parent);
    void rotation_left(RBNode **nav);
    void rotation_right(RBNode **nav);
    void print_node(Node *node);

private:
    RBNode **get_node_reference(RBNode **nav);
    void rotation_left_on_parent(RBNode *nav);
    void rotation_right_on_parent(RBNode *nav);

public:
    bool insert_node(int value);
    bool delete_node(int value);
};