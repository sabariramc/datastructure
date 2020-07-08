#include "bst.h"
#include <iostream>
using namespace std;

BinaryTree::Node **BST::search(Node **nav, int value)
{
    while (*nav != nullptr)
    {
        int node_value = (*nav)->value;
        if (node_value == value)
        {
            break;
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
    return nav;
}

bool BST::insert_node(int value)
{
    Node **nav = search(&root, value);
    if (*nav == nullptr)
    {
        *nav = new Node(value);
        size++;
    }
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
    Node **nav = search(&root, value);
    if (*nav != nullptr && (*nav)->value == value)
        return &((*nav)->value);
    return nullptr;
}

bool BST::delete_node(int value)
{
    Node **nav = search(&root, value);
    bool found = delete_node(nav, value);
    if (found)
        size--;
    return found;
}

bool BST::delete_node(Node **nav, int value)
{
    if (*nav != nullptr)
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
    return false;
}