#include "stack.h"
#include "exception.h"

#include <iostream>
using namespace std;

void test_stack()
{
    Stack s;
    int instruction;
    int value;
    while (true)
    {
        cin >> instruction;
        switch (instruction)
        {
        case 1:
            cin >> value;
            s.push(value);
            break;
        case 2:
            s.print();
            break;
        case 3:
            try
            {
                cout << s.pop() << endl;
            }
            catch (const ListEmpty &e)
            {
                cerr << e.what() << '\n';
            }
            break;
        case 4:
            return;
        default:
            break;
        }
    }
}