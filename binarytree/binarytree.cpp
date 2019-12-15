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
    node *temp = new node(value);
    node **nav = &root;
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

void BinaryTree::print_inorder(node *temp)
{
    if (temp == nullptr)
    {
        return;
    }
    print_inorder(temp->left);
    cout << temp->value << " ";
    print_inorder(temp->right);
}

void BinaryTree::print_preorder(node *temp)
{
    if (temp == nullptr)
    {
        return;
    }
    cout << temp->value << " ";
    print_preorder(temp->left);
    print_preorder(temp->right);
}

void BinaryTree::print_postorder(node *temp)
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