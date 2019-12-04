#include "linkedlist.h"
#include "exception.h"
#include <iostream>
using namespace std;

void DoublyLinkedList::insert_at_head(int value)
{
    insert(value, position_head);
}

void DoublyLinkedList::insert_at_tail(int value)
{
    insert(value, position_tail);
}

int DoublyLinkedList::peak_head()
{
    if (size == 0)
        throw ListEmpty();
    return head->value;
}

int DoublyLinkedList::peak_tail()
{
    if (size == 0)
        throw ListEmpty();
    return tail->value;
}

int DoublyLinkedList::get_head()
{
    return get(position_head);
}

int DoublyLinkedList::get_tail()
{
    return get(position_tail);
}

int DoublyLinkedList::get_size()
{
    return size;
}

void DoublyLinkedList::initiate_list(int value)
{
    Node *node = new Node(value);
    head = node;
    tail = node;
    size = 1;
}

void DoublyLinkedList::insert(int value, int position)
{
    if (size == 0)
        return initiate_list(value);
    Node *node = new Node(value);
    if (position == position_head)
    {
        node->next = head;
        head->prev = node;
        head = node;
    }
    else
    {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    size++;
}

int DoublyLinkedList::get(int position)
{
    if (size == 0)
        throw ListEmpty();
    else if (size == 1)
    {
        int value = head->value;
        terminate_list();
        return value;
    }
    Node *node;
    if (position == position_head)
    {
        Node *node = head;
        head = head->next;
        head->prev = nullptr;
    }
    else
    {
        node = tail;
        tail = node->prev;
        tail->next = nullptr;
    }
    size--;
    node->next = nullptr;
    node->prev = nullptr;
    int value = node->value;
    delete (node);
    return value;
}

void DoublyLinkedList::terminate_list()
{
    size = 0;
    delete (head);
    head = nullptr;
    tail = nullptr;
}