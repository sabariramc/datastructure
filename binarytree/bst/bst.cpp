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
    if (size > 0)
    {
        try
        {
            test_node(root);
        }
        catch (const std::exception &e)
        {
            return false;
        }
    }
    else
    {
        cout << "Tree Empty";
    }
    return true;
}

int BST::test_node(Node *nav)
{
    if (nav == nullptr)
    {
        return -2147483648;
    }
    int left = test_node(nav->left);
    int right = test_node(nav->right);
    int value = nav->value;
    if ((nav->left != nullptr && left >= value) || (nav->right != nullptr && right < value))
    {
        cout << "Integrity lost at node " << value << endl;
        throw exception();
    }
    int max = value;
    if (nav->right != nullptr)
    {
        max = right;
    }
    return max;
}