#include "linkedlist.h"
#include "exception.h"
#include <iostream>
using namespace std;

void SinglyLinkedList::initiaze_list(int value)
{
    Node *node = new Node(value);
    head = node;
    tail = node;
}

void SinglyLinkedList::insert_at_head(int value)
{
    if (size == 0)
        return initiaze_list(value);
    Node *node = new Node(value);
    node->next = head;
    head = node;
    size++;
}

void SinglyLinkedList::insert_at_tail(int value)
{
    if (size == 0)
        return initiaze_list(value);
    Node *node = new Node(value);
    tail->next = node;
    tail = node;
    size++;
}

int SinglyLinkedList::peak_head()
{
    if (size == 0)
        throw ListEmpty();
    return head->value;
}

int SinglyLinkedList::peak_tail()
{
    if (size == 0)
        throw ListEmpty();
    return tail->value;
}

int SinglyLinkedList::get_head()
{
    if (size == 1)
    {
        return terminate_list();
    }
    else if (size == 0)
    {
        throw ListEmpty();
    }
}

int SinglyLinkedList::terminate_list()
{
    size = 0;
    head = nullptr;
    int value = tail->value;
    delete (tail);
    tail = nullptr;
    return value;
}