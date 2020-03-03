#include "stack.h"
#include "redblack.h"

#include <vector>
using namespace std;

#ifndef BTREE_H
#define BTREE_H

class BTree
{
private:
    const int minimum_degree;
    const int max_key_size;
    const int min_key_requirement;
    struct Node
    {
        bool is_leaf;
        int no_of_key;
        vector<int> key;
        vector<Node *> next_ptr;
        Node(int key_size)
        {
            is_leaf = true;
            no_of_key = 0;
            vector<int> temp_key(key_size, 0);
            vector<Node *> temp_node(key_size + 1, nullptr);
            key = temp_key;
            next_ptr = temp_node;
        }
        ~Node()
        {
            for (int i = 0; i <= no_of_key; i++)
            {
                delete next_ptr[i];
                next_ptr[i] = nullptr;
            }
            key.clear();
            next_ptr.clear();
        }
    };
    int size;
    Node *root;
    void split_node(Node *nav, int child_index);
    bool add_in_non_full_node(Node *nav, int value);
    int *check_key(Node *nav, int value);
    void print_inorder(Node *nav);
    void print_preorder(Node *nav);
    bool test_properties(Node *nav, int height, RedBlack &height_track, Stack &inorder_value);
    Node *decend(Node *nav, int child_index);
    void delete_key(Node *nav, int value);
    void delete_node(Node *nav);

public:
    BTree(int degree);
    ~BTree();
    bool add(int value);
    bool remove(int value);
    const int *search(int value);
    bool test_integrity();
    void print();
    int get_size()
    {
        return size;
    }
};

#endif // !BTREE_H
