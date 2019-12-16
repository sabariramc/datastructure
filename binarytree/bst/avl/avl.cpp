#include "avl.h"
#include <iostream>

void AVL::insert_node(int value)
{
    AVLNode **nav = (AVLNode **)&root;
    insert_node(nav, value);
    size++;
}

int AVL::insert_node(AVLNode **nav, int value)
{
    if (*nav == nullptr)
    {
        AVLNode *temp = new AVLNode(value);
        *nav = temp;
        size++;
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
    check_tree_balance(nav);
    temp = *nav;
    int lh = temp->left_height;
    int rh = temp->right_height;
    return lh > rh ? lh : rh;
}

void AVL::check_tree_balance(AVLNode **nav)
{
    AVLNode *temp = *nav;
    temp->balance_factor = temp->right_height - temp->left_height;
    if (temp->balance_factor < -1)
    {
        temp = (AVLNode *)temp->left;
        if (temp->balance_factor < 0)
        {
            rotation_left_left(nav);
        }
        else
        {
            rotation_left_right(nav);
        }
    }
    else if (temp->balance_factor > 1)
    {
        temp = (AVLNode *)temp->right;
        if (temp->balance_factor < 0)
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
    AVLNode *temp = *nav;
}

void AVL::rotation_left_right(AVLNode **nav)
{
    AVLNode *temp = *nav;
}

void AVL::rotation_right_left(AVLNode **nav)
{
    AVLNode *temp = *nav;
}

void AVL::rotation_right_right(AVLNode **nav)
{
    AVLNode *temp = *nav;
}
