#include <iostream>

#ifndef HEAP_H
#define HEAP_H

class Heap
{
private:
    int *arr;
    int length = 0;
    int capacity = 0;
    void heapify(int index);
    void reallocate(int capicity);
    void swap(int idx1, int idx2);
    void test_integrity(int index, int value);

public:
    Heap()
    {
        arr = new int(16);
        capacity = 16;
    }
    ~Heap()
    {
        delete[] arr;
    }
    int get();
    int peek();
    void add(int value);
    int size() { return length; }
    bool is_empty() { return size() == 0; }
    void print();
    void test_integrity();
};

#endif // !HEAP_H