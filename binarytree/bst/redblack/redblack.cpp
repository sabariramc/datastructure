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
    RBNode **nav = (RBNode **)&root;
    int result = delete_node(nav, value);
    if (result > -1)
    {
        size--;
        cout << "Value deleted from tree\n";
        return true;
    }
    else
    {
        cout << "Value not found in the tree\n";
        return false;
    }
}

void RedBlack::insert_node(RBNode **nav, RBNode *p, int &value)
{
    if (*nav == nullptr)
    {
        *nav = new RBNode(value);
        (*nav)->parent = p;
        insert_fix_up(nav);
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
    if (*nav == nullptr)
    {
        return -1;
    }
    RBNode *temp = *nav;
    RBNode *temp_parent;
    if (temp->value == value)
    {
        enum COLOUR original_color = temp->color;
        if (temp->right != nullptr && temp->left != nullptr)
        {
            temp = (RBNode *)temp->right;
            while (temp->left != nullptr)
            {
                temp = (RBNode *)temp->left;
            }
            temp_parent = temp->parent;
            original_color = temp->color;
        }
        else
        {
            if (temp->left == nullptr)
            {
                temp_parent = temp->parent;
                temp = (RBNode *)temp->left;
            }
            else if (temp->right == nullptr)
            {
                temp_parent = temp->parent;
                temp = (RBNode *)temp->right;
            }
            else
            {
                temp_parent = temp->parent;
                temp = nullptr;
            }
        }
        delete_node((Node *)temp);
        if (original_color == BLACK)
        {
            delete_fix_up()
        }
    }
    else if (temp->value > value)
    {
        delete_node((RBNode **)&(temp->left), value);
    }
    else
    {
        delete_node((RBNode **)&(temp->right), value);
    }
    return 1;
}

void RedBlack::insert_fix_up(RBNode **nav)
{
    RBNode *node = *nav;
    while (node->parent != nullptr && node->parent->color == RED)
    {
        if (node->parent == node->parent->parent->left)
        {
            RBNode *uncle = (RBNode *)node->parent->parent->right;
            if (uncle != nullptr && uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    rotation_left(&(node->parent));
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotation_right(&(node->parent->parent));
            }
        }
        else
        {
            RBNode *uncle = (RBNode *)node->parent->parent->left;
            if (uncle != nullptr && uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    rotation_right(&(node->parent));
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotation_left(&(node->parent->parent));
            }
        }
    }
    node = (RBNode *)root;
    node->color = BLACK;
}

void RedBlack::delete_fix_up(RBNode **nav)
{
}

void RedBlack::rotation_left(RBNode **nav)
{
    nav = get_node_reference(nav);
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
    nav = get_node_reference(nav);
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

RedBlack::RBNode **RedBlack::get_node_reference(RBNode **nav)
{
    RBNode *node = *nav;
    if (node == root)
    {
        nav = (RBNode **)&root;
    }
    else if (node->parent->right == node)
    {
        nav = (RBNode **)&(node->parent->right);
    }
    else
    {
        nav = (RBNode **)&(node->parent->left);
    }
    return nav;
}

void RedBlack::print_node(Node *node)
{
    RBNode *temp = (RBNode *)node;
    cout << temp->value << "(" << temp->color << ")";
}
