#include <iostream>

#include <vector>

#ifndef INDEXED_PRIORITY_QUEUE_H
#define INDEXED_PRIORITY_QUEUE_H

class IndexedPriorityQueue
{
private:
    // int *priority;
    // int *pm;
    // int *im;
    std::vector<int> priority;
    std::vector<int>pm;
    std::vector<int>im;
    int size = 0;
    int capacity = 0;

    void swap(int i, int j);
    void swim(int i);
    void sink(int i);

public:
    IndexedPriorityQueue(int capacity);
    ~IndexedPriorityQueue();
    void insert(int key, int priority);
    int poll();
    void remove(int key);
    void update(int key, int priority);
    void increase(int key, int value);
    void decrease(int key, int value);
    int peek();
    void print();
    bool test_integrity();
    bool test_integrity(int index, int value);
};

#endif // !INDEXED_PRIORITY_QUEUE_H
