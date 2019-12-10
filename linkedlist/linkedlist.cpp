#include "linkedlist.h"
#include "exception.h"
#include <iostream>
using namespace std;

void doublylinkedlist::insert_at_head(int value)
{
    insert(value, position_head);
}

void doublylinkedlist::insert_at_tail(int value)
{
    insert(value, position_tail);
}

int doublylinkedlist::peak_head()
{
    if (size == 0)
        throw ListEmpty();
    return head->value;
}

int doublylinkedlist::peak_tail()
{
    if (size == 0)
        throw ListEmpty();
    return tail->value;
}

int doublylinkedlist::get_head()
{
    return get(position_head);
}

int doublylinkedlist::get_tail()
{
    return get(position_tail);
}

int doublylinkedlist::get_size()
{
    return size;
}

void doublylinkedlist::initiate_list(int value)
{
    Node *node = new Node(value);
    head = node;
    tail = node;
    size = 1;
}

void doublylinkedlist::insert(int value, int position)
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

int doublylinkedlist::get(int position)
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
        node = head;
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

void doublylinkedlist::terminate_list()
{
    size = 0;
    delete (head);
    head = nullptr;
    tail = nullptr;
}

void doublylinkedlist::print()
{
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->value << " ";
        temp = temp->next;
    }
    cout << endl;
}