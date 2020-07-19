#include <iostream>

using namespace std;

#ifndef FENWICK_TREE_H
#define FENWICK_TREE_H

class BinaryIndexedTree
{
private:
    int *tree;
    int *arr;
    int len;

    void point_update(int i, int value);

public:
    BinaryIndexedTree(int arr[], int len);
    ~BinaryIndexedTree()
    {
        delete[] arr;
        delete[] tree;
    }
    int lsb(int i)
    {
        return i & -i;
    }
    void print()
    {
        cout << "Value : ";
        for (int i = 0; i < len; i++)
            cout << arr[i] << " ";
        cout << "\nTree  : ";
        for (int i = 0; i < len; i++)
            cout << tree[i + 1] << " ";
        cout << "\n";
    }
    int range_query(int from_index, int to_index)
    {
        if (from_index >= 0 && from_index < len && to_index >= 0 && to_index < len && from_index < to_index)
            return prefix_query(to_index) - prefix_query(from_index - 1);
        return -1;
    }
    int prefix_query(int index);
    void set(int index, int value);
    void update(int index, int value);
};

#endif // !FENWICK_TREE_H
