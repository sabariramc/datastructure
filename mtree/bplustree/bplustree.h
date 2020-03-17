#include "stack.h"
#include "redblack.h"

#include <vector>
#include <string>
using namespace std;

#ifndef BPlusTree_H
#define BPlusTree_H

class BPlusTree
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
        vector<string *> data_ptr;
        Node *adjusant_ptr;
        ~Node()
        {
            if (is_leaf)
            {
                for (int i = 0; i <= no_of_key; i++)
                {
                    delete data_ptr[i];
                    data_ptr[i] = nullptr;
                }
                adjusant_ptr = nullptr;
            }
            else
            {
                for (int i = 0; i <= no_of_key; i++)
                {
                    delete next_ptr[i];
                    next_ptr[i] = nullptr;
                }
            }
            key.clear();
            next_ptr.clear();
        }
        static Node *get_new_internal_node(int key_size)
        {
            Node *new_node = new Node(key_size);
            vector<Node *> temp_node(key_size + 1, nullptr);
            new_node->next_ptr = temp_node;
            new_node->is_leaf = false;
            return new_node;
        }
        static Node *get_new_leaf_node(int key_size)
        {
            Node *new_node = new Node(key_size);
            vector<string *> temp_node(key_size, nullptr);
            new_node->data_ptr = temp_node;
            new_node->is_leaf = true;
            return new_node;
        }

    private:
        Node(int key_size)
        {
            no_of_key = 0;
            vector<int> temp_key(key_size, 0);
            adjusant_ptr = nullptr;
            vector<Node *> temp_node(key_size + 1, nullptr);
            key = temp_key;
            next_ptr = temp_node;
        }
    };
    int size;
    int height;
    Node *root;
    void split_node(Node *nav, int child_index);
    bool add_in_non_full_node(Node *nav, int key, string *value);
    int *check_key(Node *nav, int value);
    void print_inorder(Node *nav);
    void print_preorder(Node *nav);
    bool test_properties(Node *nav, int height, RedBlack &height_track, Stack &inorder_value, RedBlack &leaf_key_track, Stack &internal_node_track);
    void delete_key(Node *nav, int value);
    void delete_node(Node *nav);

public:
    BPlusTree(int degree);
    ~BPlusTree();
    bool add(int key, string value);
    bool remove(int key);
    const string *search(int key);
    bool test_integrity();
    void print();
    int get_size()
    {
        return size;
    }
    int get_height()
    {
        return height;
    }
};

#endif // !BPlusTree_H
