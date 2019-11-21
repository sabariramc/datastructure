#include "linkedlist.h"
#include <iostream>
using namespace std;

void SinglyLinkedList::insert_at_head(int value)
{
    Node *node = new Node(value);
    if (head == nullptr)
        tail = node;
    node->next = head;
    head = node;
    size++;
}

void SinglyLinkedList::insert_at_tail(int value)
{
    Node *node = new Node(value);
    Node **tail_ptr = &tail;
    if (tail == nullptr)
        head = node;
    while (*tail_ptr != nullptr)
        tail_ptr = &(tail->next);
    *tail_ptr = node;
    tail = node;
    size++;
}