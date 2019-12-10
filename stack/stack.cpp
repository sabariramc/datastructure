#include "stack.h"
#include <iostream>
using namespace std;

void Stack::push(int value)
{
    stack.insert_at_head(value);
}

int Stack::pop()
{
    return stack.get_head();
}

int Stack::size()
{
    return stack.get_size();
}

int Stack::peak()
{
    return stack.peak_head();
}

void Stack::print()
{
    if (stack.get_size() <= 0)
    {
        cout << "Stack Empty";
    }
    else
    {
        cout << "From Top Down:\n";
        stack.print();
    }
}