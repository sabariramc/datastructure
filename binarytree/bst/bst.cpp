#include "bst.h"

bool BST::insert_node(int value)
{
    Node *temp = new Node(value);
    Node **nav = &root;
    while (*nav != nullptr)
    {
        if ((*nav)->value > value)
        {
            nav = &((*nav)->left);
        }
        else
        {
            nav = &((*nav)->right);
        }
    }
    *nav = temp;
    size++;
    return true;
}