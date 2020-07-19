#include "binaryindexedtree.h"

BinaryIndexedTree::BinaryIndexedTree(int arr[], int len)
{
    this->len = len;
    this->arr = new int[len];
    tree = new int[len + 1]{0};
    for (int i = 0; i < len; i++)
    {
        this->arr[i] = arr[i];
        point_update(i, arr[i]);
    }
}

void BinaryIndexedTree::point_update(int index, int value)
{
    index++;
    while (index <= len)
    {
        tree[index] += value;
        index += lsb(index);
    }
}

int BinaryIndexedTree::prefix_query(int index)
{
    index++;
    int sum = 0;
    while (index <= len && index > 0)
    {
        sum += tree[index];
        index &= ~lsb(index);
    }
    return sum;
}

void BinaryIndexedTree::set(int index, int value)
{
    if (index >= 0 && index < len)
    {
        int diff = value - arr[index];
        arr[index] = value;
        point_update(index, diff);
    }
}

void BinaryIndexedTree::update(int index, int value)
{
    if (index >= 0 && index < len)
    {
        arr[index] += value;
        point_update(index, value);
    }
}