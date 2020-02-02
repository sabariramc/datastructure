#include "btree.h"

BTree::BTree(int minimum_degree) : minimum_degree(minimum_degree), max_key_size((2 * minimum_degree) - 1), min_key_requirement(minimum_degree - 1)
{
    if (minimum_degree < 2)
    {
        throw "Minimum degree cannot be less than 2";
    }
    root = nullptr;
}

BTree::~BTree()
{
    delete root;
    root = nullptr;
}

const int *BTree::search_value(int value)
{
    Node *nav;
    while (nav != nullptr)
    {
        int start = 0;
        int end = nav->no_of_key;
        int next_ptr_index;
        int *keys = nav->value;
        while (start < end)
        {
            int diff = end - start;
            int mid = (start + end) / 2;
            if (keys[mid] == value)
            {
                return keys + mid;
            }
            else if (diff <= 1)
            {
                if (value < keys[start])
                    next_ptr_index = start;
                else if (value > keys[end])
                    next_ptr_index = end + 1;
                else if (value == keys[end])
                    return keys + end;
                else
                    next_ptr_index = end;
                break;
            }
            else if (keys[mid] > value)
            {
                end = mid;
            }
            else
            {
                start = mid;
            }
        }
        nav = nav->next_ptr[next_ptr_index];
    }
    return nullptr;
}