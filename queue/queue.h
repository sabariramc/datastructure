#include "linkedlist.h"

class Queue
{
public:
    void enqueue(int value);
    int peak();
    int dequeue();
    int size();
    void print();

private:
    doublylinkedlist queue;
};