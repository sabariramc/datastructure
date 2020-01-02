#include "bst.h"
#include <iostream>
using namespace std;

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

bool BST::test_tree_integraty()
{
    test_node_value(root);
}

int BST::test_node_value(Node *nav)
{
    if (nav == nullptr)
    {
        return -2147483648;
    }
    int left = test_node_value(nav->left);
    int right = test_node_value(nav->right);
    int value = nav->value;
    if ((nav->left != nullptr && left >= value) || (nav->right != nullptr && right < value))
    {
        cout << "Node Value integrity lost at node " << value << endl;
    }
    int max = value;
    if (nav->right != nullptr)
    {
        max = right;
    }
    return max;
}