#include "stack.h"

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