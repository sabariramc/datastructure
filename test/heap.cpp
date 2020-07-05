#include "heap.h"

#include <iostream>
using namespace std;

void test_heap()
{
    Heap h;
    int instruction;
    int value;
    while (true)
    {
        cin >> instruction;
        switch (instruction)
        {
        case 1:
            cin >> value;
            cout << "Add :" << value << endl;
            h.add(value);
            h.print();
            h.test_integrity();
            break;
        case 2:
            cout << "Polled: " << h.get() << endl;
            h.test_integrity();
            h.print();
            break;
        case 3:
            cout << "Peak: " << h.peek() << endl;
            break;
        case 4:
            h.print();
            break;
        case 5:
            return;
        default:
            break;
        }
    }
}
