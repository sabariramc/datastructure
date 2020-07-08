#include "bst.h"
#include <iostream>
using namespace std;

bool BST::insert_node(int value)
{
    Node *temp = new Node(value);
    Node **nav = &root;
    while (*nav != nullptr)
    {
        int node_value = (*nav)->value;
        if (node_value == value)
        {
            return false;
        }
        else if (node_value > value)
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

const int *BST::search(int value)
{
    Node *nav = root;
    while (nav != nullptr)
    {
        if (nav->value == value)
        {
            return &(nav->value);
        }
        else if (nav->value < value)
        {
            nav = nav->right;
        }
        else
        {
            nav = nav->left;
        }
    }
    return nullptr;
}

bool BST::delete_node(int value)
{
    Node **nav = &root;
    bool found = delete_node(nav, value);
    if (found)
        size--;
    return found;
}

bool BST::delete_node(Node **nav, int value)
{
    if (*nav == nullptr)
    {
        return false;
    }
    while (*nav != nullptr)
    {
        if ((*nav)->value == value)
        {
            Node *temp = *nav;
            if (temp->left == nullptr)
            {
                *nav = temp->right;
            }
            else if (temp->right == nullptr)
            {
                *nav = temp->left;
            }
            else
            {
                Node **temp_left = &(temp->left);
                while ((*temp_left)->right != nullptr)
                {
                    temp_left = &((*temp_left)->right);
                }
                Node *sucessor = *temp_left;
                if (temp->left != *temp_left)
                {
                    *temp_left = sucessor->left;
                    sucessor->left = temp->left;
                }
                sucessor->right = temp->right;
                *nav = sucessor;
            }
            delete_node(temp);
            return true;
        }
        else if ((*nav)->value > value)
        {
            nav = &((*nav)->left);
        }
        else
        {
            nav = &((*nav)->right);
        }
    }
    return false;
}