#include "avl.h"
#include <iostream>
using namespace std;

bool AVL::insert_node(int value)
{
    AVLNode **nav = (AVLNode **)&root;
    insert_node(nav, value);
    size++;
    return true;
}

int AVL::insert_node(AVLNode **nav, int value)
{
    if (*nav == nullptr)
    {
        AVLNode *temp = new AVLNode(value);
        *nav = temp;
        return 1;
    }
    AVLNode *temp = *nav;
    if ((*nav)->value > value)
    {
        AVLNode **left = (AVLNode **)&((*nav)->left);
        temp->left_height = insert_node(left, value);
    }
    else
    {
        AVLNode **right = (AVLNode **)&((*nav)->right);
        temp->right_height = insert_node(right, value);
    }
    check_height_balance(nav);
    temp = *nav;
    int lh = temp->left_height;
    int rh = temp->right_height;
    return lh > rh ? lh + 1 : rh + 1;
}

bool AVL::delete_node(int value)
{
    AVLNode **nav = (AVLNode **)&root;
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

int AVL::delete_node(AVLNode **nav, int value)
{
    if (*nav == nullptr)
    {
        return -1;
    }
    AVLNode *temp = *nav;
    int new_height = -1;
    if (temp->value == value)
    {
        if (temp->left == nullptr)
        {
            *nav = (AVLNode *)temp->right;
            new_height = temp->right_height;
        }
        else
        {
            new_height = delete_node_by_copying(nav, (AVLNode **)&temp->left);
            (*nav)->left_height = new_height;
            int lh = new_height;
            int rh = (*nav)->right_height;
            new_height = lh > rh ? lh + 1 : rh + 1;
        }
        delete_node((Node *)temp);
        return new_height;
    }
    else if (temp->value > value)
    {
        new_height = delete_node((AVLNode **)&(temp->left), value);
        if (new_height > -1)
        {
            temp->left_height = new_height;
        }
    }
    else
    {
        new_height = delete_node((AVLNode **)&(temp->right), value);
        if (new_height > -1)
        {
            temp->right_height = new_height;
        }
    }
    if (new_height > -1)
    {
        check_height_balance(nav);
        temp = *nav;
        int lh = temp->left_height;
        int rh = temp->right_height;
        return lh > rh ? lh + 1 : rh + 1;
    }
    else
        return -1;
}

int AVL::delete_node_by_copying(AVLNode **target, AVLNode **nav)
{
    AVLNode *temp = *nav;
    if (temp->right == nullptr)
    {

        AVLNode *temp_left = (AVLNode *)temp->left;
        temp->right_height = (*target)->right_height;
        *nav = (AVLNode *)temp->left;
        int lh = temp->left_height;
        temp->right = (*target)->right;
        temp->left = (*target)->left;
        *target = temp;
        return lh;
    }
    else
    {
        int rh = delete_node_by_copying(target, (AVLNode **)&temp->right);
        temp->right_height = rh;
        check_height_balance(nav);
        temp = *nav;
        int lh = temp->left_height;
        return lh > rh ? lh + 1 : rh + 1;
    }
}

void AVL::check_height_balance(AVLNode **nav)
{
    AVLNode *temp = *nav;
    int balance_factor = temp->right_height - temp->left_height;
    if (balance_factor < -1)
    {
        temp = (AVLNode *)temp->left;
        if (balance_factor <= 0)
        {
            rotation_left_left(nav);
        }
        else
        {
            rotation_left_right(nav);
        }
    }
    else if (balance_factor > 1)
    {
        temp = (AVLNode *)temp->right;
        if (balance_factor < 0)
        {
            rotation_right_left(nav);
        }
        else
        {
            rotation_right_right(nav);
        }
    }
}

void AVL::rotation_left_left(AVLNode **nav)
{
    AVLNode *node = *nav;
    AVLNode *left = (AVLNode *)node->left;
    AVLNode *left_right = (AVLNode *)left->right;
    *nav = left;
    left->right = node;
    node->left = left_right;
    node->left_height = left->right_height;
    int lh = node->left_height;
    int rh = node->right_height;
    left->right_height = lh > rh ? lh + 1 : rh + 1;
}

void AVL::rotation_left_right(AVLNode **nav)
{
    AVLNode *node = *nav;
    AVLNode *left = (AVLNode *)node->left;
    AVLNode *left_right = (AVLNode *)left->right;
    AVLNode *left_right_left = (AVLNode *)left_right->left;
    AVLNode *left_right_right = (AVLNode *)left_right->right;
    *nav = left_right;
    left_right->right = node;
    left_right->left = left;
    left->right = left_right_left;
    node->left = left_right_right;
    left->right_height = left_right->left_height;
    node->left_height = left_right->right_height;
    int lh = left->left_height;
    int rh = left->right_height;
    left_right->left_height = lh > rh ? lh + 1 : rh + 1;
    lh = node->left_height;
    rh = node->right_height;
    left_right->right_height = lh > rh ? lh + 1 : rh + 1;
}

void AVL::rotation_right_right(AVLNode **nav)
{
    AVLNode *node = *nav;
    AVLNode *right = (AVLNode *)node->right;
    AVLNode *right_left = (AVLNode *)right->left;
    *nav = right;
    right->left = node;
    node->right = right_left;
    node->right_height = right->left_height;
    int lh = node->left_height;
    int rh = node->right_height;
    right->left_height = lh > rh ? lh + 1 : rh + 1;
}

void AVL::rotation_right_left(AVLNode **nav)
{
    AVLNode *node = *nav;
    AVLNode *right = (AVLNode *)node->right;
    AVLNode *right_left = (AVLNode *)right->left;
    AVLNode *right_left_left = (AVLNode *)right_left->left;
    AVLNode *right_left_right = (AVLNode *)right_left->right;
    *nav = right_left;
    right_left->right = right;
    right_left->left = node;
    right->left = right_left_right;
    node->right = right_left_left;
    right->left_height = right_left->right_height;
    node->right_height = right_left->left_height;
    int lh = right->left_height;
    int rh = right->right_height;
    right_left->right_height = lh > rh ? lh + 1 : rh + 1;
    lh = node->left_height;
    rh = node->right_height;
    right_left->left_height = lh > rh ? lh + 1 : rh + 1;
}

void AVL::print_node(Node *node)
{
    AVLNode *temp = (AVLNode *)node;
    int lh = temp->left_height;
    int rh = temp->right_height;
    cout << temp->value << "(" << lh << "," << rh << "," << rh - lh << ")";
}