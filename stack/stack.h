#include "linkedlist/linkedlist.h"
#include "linkedlist/exception.h"

class Stack
{
public:
    void push(int value);
    int peak();
    int pop();

private:
    DoublyLinkedList stack;
};