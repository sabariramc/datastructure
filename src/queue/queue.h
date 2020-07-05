#include "linkedlist.h"

#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
public:
    void enqueue(int value);
    const int *peak();
    int dequeue();
    int size();
    void print();

private:
    DoublyLinkedList queue;
};

#endif // !QUEUE_H
