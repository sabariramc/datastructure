#include <exception>
#include <iostream>

using namespace std;

#include "stack.h"

int main(int argc, const char **argv)
{
    Stack s;
    s.push(1);
    cout << s.pop();
    return 0;
}