#include "linkedlist.h"

#ifndef STACH_H
#define STACH_H

class Stack
{
public:
    void push(int value);
    const int *peak();
    int pop();
    int size();
    void print();

private:
    DoublyLinkedList stack;
};

#endif // !STACH_H
