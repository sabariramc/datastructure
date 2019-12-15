#include "binarytree.h"
#include "stack.h"
#include <iostream>
using namespace std;

BinaryTree::BinaryTree()
{
    root = nullptr;
}

BinaryTree::~BinaryTree()
{
    delete (root);
    root = nullptr;
}

void BinaryTree::insert_node(int value)
{
    Node *temp = new Node(value);
    Node **nav = &root;
    int curr_size = size + 1, next_bit;
    Stack s;
    while (curr_size)
    {
        s.push(curr_size % 2);
        curr_size >>= 1;
    }
    s.pop();
    while (*nav != nullptr)
    {
        next_bit = s.pop();
        if (next_bit)
        {
            nav = &((*nav)->right);
        }
        else
        {
            nav = &((*nav)->left);
        }
    }
    *nav = temp;
    size++;
}

void BinaryTree::delete_node(int value)
{
    Node **nav = &root;
    bool found = delete_node(nav, value);
    if (found)
    {
        cout << "Value deleted from the tree\n";
    }
    else
    {
        cout << "Value not found in the tree\n";
    }
}

bool BinaryTree::delete_node(Node **nav, int value)
{
    if (*nav == nullptr)
    {
        return false;
    }
    Node *temp = *nav;
    if (temp->value == value)
    {
        if (temp->left != nullptr)
        {
            *nav = temp->left;
            while (*nav != nullptr)
            {
                nav = &((*nav)->right);
            }
            *nav = temp->right;
        }
        else
        {
            *nav = temp->right;
        }
        temp->left = nullptr;
        temp->right = nullptr;
        delete (temp);
        size--;
        return true;
    }
    bool found = delete_node(&(temp->left), value);
    if (found)
        return found;
    found = delete_node(&(temp->right), value);
    return found;
}

void BinaryTree::print_inorder(Node *temp)
{
    if (temp == nullptr)
    {
        return;
    }
    print_inorder(temp->left);
    cout << temp->value << " ";
    print_inorder(temp->right);
}

void BinaryTree::print_preorder(Node *temp)
{
    if (temp == nullptr)
    {
        return;
    }
    cout << temp->value << " ";
    print_preorder(temp->left);
    print_preorder(temp->right);
}

void BinaryTree::print_postorder(Node *temp)
{
    if (temp == nullptr)
    {
        return;
    }
    print_postorder(temp->left);
    print_postorder(temp->right);
    cout << temp->value << " ";
}

void BinaryTree::print()
{
    if (size == 0)
    {
        cout << "Empty Tree\n";
        return;
    }
    cout << "Inorder Traversal:";
    print_inorder(root);
    cout << "\nPreorder Traversal:";
    print_preorder(root);
    cout << "\nPostorder Traversal:";
    print_postorder(root);
    cout << endl;
}