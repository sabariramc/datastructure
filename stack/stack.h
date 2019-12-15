#include "linkedlist.h"

class Stack
{
public:
    void push(int value);
    int peak();
    int pop();
    int size();
    void print();

private:
    DoublyLinkedList stack;
};