#include "queue.h"
#include <iostream>
using namespace std;

void Queue::enqueue(int value)
{
    queue.insert_at_tail(value);
}

int Queue::dequeue()
{
    return queue.get_head();
}

int Queue::size()
{
    return queue.get_size();
}

int Queue::peak()
{
    return queue.peak_head();
}

void Queue::print()
{
    if (queue.get_size() <= 0)
    {
        cout << "Queue Empty";
    }
    else
    {
        cout << "From First to Last:\n";
        queue.print();
    }
}