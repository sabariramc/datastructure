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
    return lh > rh ? lh + 1 : rh + 1;
}

void AVL::check_tree_balance(AVLNode **nav)
{
    AVLNode *temp = *nav;
    int balance_factor = temp->right_height - temp->left_height;
    if (balance_factor < -1)
    {
        temp = (AVLNode *)temp->left;
        if (balance_factor < 0)
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
