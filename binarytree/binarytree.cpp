#include "binarytree.h"

#include <iostream>
using namespace std;

binarytree::binarytree()
{
    root = nullptr;
}

binarytree::~binarytree()
{
    delete (root);
    root = nullptr;
}

void binarytree::insert_node(int value)
{
    node *temp = new node(value);
    node **nav = &root;
    int curr_size = size;
    while (*nav != nullptr)
    {
        if (curr_size % 2)
        {
            nav = &((*nav)->right);
        }
        else
        {
            nav = &((*nav)->left);
        }
        curr_size >>= 1;
    }
    *nav = temp;
    size++;
}

void binarytree::print_inorder(node *temp)
{
    if (temp == nullptr)
    {
        return;
    }
    print_inorder(temp->left);
    cout << temp->value << " ";
    print_inorder(temp->right);
}

void binarytree::print_preorder(node *temp)
{
    if (temp == nullptr)
    {
        return;
    }
    cout << temp->value << " ";
    print_preorder(temp->left);
    print_preorder(temp->right);
}

void binarytree::print_postorder(node *temp)
{
    if (temp == nullptr)
    {
        return;
    }
    print_postorder(temp->left);
    print_postorder(temp->right);
    cout << temp->value << " ";
}

void binarytree::print()
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