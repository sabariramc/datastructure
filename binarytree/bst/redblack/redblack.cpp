#include "redblack.h"
#include <iostream>
using namespace std;

bool RedBlack::insert_node(int value)
{
    RBNode **nav = (RBNode **)&root;
    insert_node(nav, nullptr, value);
    size++;
    return true;
}

bool RedBlack::delete_node(int value)
{
}

void RedBlack::insert_node(RBNode **nav, RBNode *p, int &value)
{
    if (*nav == nullptr)
    {
        *nav = new RBNode(value);
        (*nav)->parent = p;
        check_rule_violation(nav);
        return;
    }
    RBNode *node = *nav;
    if (node->value > value)
    {
        insert_node((RBNode **)&node->left, node, value);
    }
    else
    {
        insert_node((RBNode **)&node->right, node, value);
    }
}

int RedBlack::delete_node(RBNode **nav, int value)
{
}

int RedBlack::delete_node_by_copying(RBNode **target, RBNode **nav)
{
}

void RedBlack::check_rule_violation(RBNode **nav)
{
}

void RedBlack::rotation_left(RBNode **nav)
{
    RBNode *node = *nav;
    RBNode *right = (RBNode *)node->right;
    RBNode *right_left = (RBNode *)right->left;
    *nav = right;
    right->parent = node->parent;
    right->left = node;
    node->parent = right;
    node->right = right_left;
    if (right_left != nullptr)
    {
        right_left->parent = node;
    }
}

void RedBlack::rotation_right(RBNode **nav)
{
    RBNode *node = *nav;
    RBNode *left = (RBNode *)node->left;
    RBNode *left_right = (RBNode *)left->right;
    *nav = left;
    left->parent = node->parent;
    left->right = node;
    node->parent = left;
    node->left = left_right;
    if (left_right != nullptr)
    {
        left_right->parent = node;
    }
}

void RedBlack::print_node(Node *node)
{
    RBNode *temp = (RBNode *)node;
    cout << temp->value << "(" << temp->node_color << ")";
}
