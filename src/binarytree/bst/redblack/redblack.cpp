#include "redblack.h"
#include <iostream>
using namespace std;

bool RedBlack::insert_node(int value)
{
    RBNode **nav = (RBNode **)&root;
    if (insert_node(nav, nullptr, value))
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
        return true;
    }
    else
    {
        return false;
    }
}

bool RedBlack::insert_node(RBNode **nav, RBNode *p, int &value)
{
    RBNode *node = *nav;
    while (*nav != nullptr)
    {
        p = node;
        if (node->value == value)
        {
            return false;
        }
        else if (node->value > value)
        {
            nav = (RBNode **)&(node->left);
        }
        else
        {
            nav = (RBNode **)&(node->right);
        }
        node = *nav;
    }
    *nav = new RBNode(value);
    (*nav)->parent = p;
    insert_fix_up(nav);
    return true;
}

int RedBlack::delete_node(RBNode **nav, int value)
{
    RBNode *temp = *nav;
    RBNode *successor_parent, *successor, *fix_up_node, *fix_up_node_parent;
    while (*nav != nullptr)
    {
        if (temp->value == value)
        {
            enum COLOUR original_color = temp->color;
            if (temp->right != nullptr && temp->left != nullptr)
            {
                successor = (RBNode *)temp->right;
                while (successor->left != nullptr)
                {
                    successor = (RBNode *)successor->left;
                }
                original_color = successor->color;
                successor->color = temp->color;
                successor_parent = successor->parent;
                successor->left = temp->left;
                ((RBNode *)temp->left)->parent = successor;
                successor->parent = temp->parent;
                fix_up_node = (RBNode *)successor->right;
                fix_up_node_parent = successor;
                if (successor_parent != temp)
                {
                    fix_up_node_parent = successor_parent;
                    RBNode *sucessor_right = (RBNode *)successor->right;
                    successor_parent->left = sucessor_right;
                    if (sucessor_right != nullptr)
                        sucessor_right->parent = successor_parent;
                    successor->right = temp->right;
                    ((RBNode *)temp->right)->parent = successor;
                }
                *nav = successor;
            }
            else
            {
                successor_parent = temp->parent;
                if (temp->left == nullptr)
                {
                    successor = (RBNode *)temp->right;
                }
                else if (temp->right == nullptr)
                {
                    successor = (RBNode *)temp->left;
                }
                else
                {
                    successor = nullptr;
                }
                *nav = successor;
                if (successor != nullptr)
                {
                    successor->parent = successor_parent;
                }
                fix_up_node_parent = successor_parent;
                fix_up_node = successor;
            }
            delete_node((Node *)temp);
            if (original_color == BLACK)
            {
                delete_fix_up(fix_up_node, fix_up_node_parent);
            }
            return 1;
        }
        else if (temp->value > value)
        {
            nav = (RBNode **)&(temp->left);
        }
        else
        {
            nav = (RBNode **)&(temp->right);
        }
        temp = *nav;
    }
    return -1;
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
                    rotation_left(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotation_right(node->parent->parent);
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
                    rotation_right(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotation_left(node->parent->parent);
            }
        }
    }
    ((RBNode *)root)->color = BLACK;
}

void RedBlack::delete_fix_up(RBNode *fix_node, RBNode *fix_node_parent)
{
    while (fix_node != root && (fix_node == nullptr || fix_node->color == BLACK))
    {
        if (fix_node_parent->left == fix_node)
        {
            RBNode *sibiling = (RBNode *)fix_node_parent->right;
            if (sibiling->color == RED)
            {
                sibiling->color = BLACK;
                fix_node_parent->color = RED;
                rotation_left(fix_node_parent);
                sibiling = (RBNode *)fix_node_parent->right;
            }
            RBNode *sibiling_left = (RBNode *)sibiling->left;
            RBNode *sibiling_right = (RBNode *)sibiling->right;
            if ((sibiling_left == nullptr || sibiling_left->color == BLACK) && (sibiling_right == nullptr || sibiling_right->color == BLACK))
            {
                sibiling->color = RED;
                fix_node = fix_node_parent;
            }
            else
            {
                if (sibiling_right == nullptr || sibiling_right->color == BLACK)
                {
                    sibiling_left->color = BLACK;
                    sibiling->color = RED;
                    rotation_right(sibiling);
                    sibiling = (RBNode *)fix_node_parent->right;
                }
                sibiling->color = fix_node_parent->color;
                fix_node_parent->color = BLACK;
                ((RBNode *)sibiling->right)->color = BLACK;
                rotation_left(fix_node_parent);
                fix_node = (RBNode *)root;
            }
        }
        else
        {
            RBNode *sibiling = (RBNode *)fix_node_parent->left;
            if (sibiling->color == RED)
            {
                sibiling->color = BLACK;
                fix_node_parent->color = RED;
                rotation_right(fix_node_parent);
                sibiling = (RBNode *)fix_node_parent->left;
            }
            RBNode *sibiling_left = (RBNode *)sibiling->left;
            RBNode *sibiling_right = (RBNode *)sibiling->right;
            if ((sibiling_left == nullptr || sibiling_left->color == BLACK) && (sibiling_right == nullptr || sibiling_right->color == BLACK))
            {
                sibiling->color = RED;
                fix_node = fix_node_parent;
                fix_node_parent = fix_node_parent->parent;
            }
            else
            {
                if (sibiling_left == nullptr || sibiling_left->color == BLACK)
                {
                    sibiling_right->color = BLACK;
                    sibiling->color = RED;
                    rotation_left(sibiling);
                    sibiling = (RBNode *)fix_node_parent->left;
                }
                sibiling->color = fix_node_parent->color;
                fix_node_parent->color = BLACK;
                ((RBNode *)sibiling->left)->color = BLACK;
                rotation_right(fix_node_parent);
                fix_node = (RBNode *)root;
            }
        }
        fix_node_parent = fix_node->parent;
    }
    if (fix_node != nullptr)
        fix_node->color = BLACK;
}

void RedBlack::rotation_left(RBNode *temp)
{
    RBNode **nav = get_node_reference(temp);
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

void RedBlack::rotation_right(RBNode *temp)
{
    RBNode **nav = get_node_reference(temp);
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

RedBlack::RBNode **RedBlack::get_node_reference(RBNode *node)
{
    RBNode **nav = nullptr;
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

bool RedBlack::test_tree_integraty()
{
    test_node_value(root);
    cout << "Size " << size << " Black height " << test_red_black_rule((RBNode *)root) << endl;
}

int RedBlack::test_red_black_rule(RBNode *nav)
{
    if (nav == nullptr)
    {
        return 0;
    }
    int left_black_height = test_red_black_rule((RBNode *)nav->left);
    int right_black_height = test_red_black_rule((RBNode *)nav->right);
    if (left_black_height != right_black_height)
    {
        cout << "Equal black height violate at " << nav->value << endl;
    }
    if (nav->parent != nullptr && nav->parent->color == RED && nav->color == RED)
    {
        std::cout << "RED node with RED children at " << nav->value << std::endl;
    }
    if (nav->color == BLACK)
    {
        left_black_height++;
    }
    return left_black_height;
}