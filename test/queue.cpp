#include "queue.h"
#include "exception.h"

#include <iostream>
using namespace std;

void test_queue()
{
    Queue q;
    int instruction;
    int value;
    while (true)
    {
        cin >> instruction;
        switch (instruction)
        {
        case 1:
            cin >> value;
            q.enqueue(value);
            break;
        case 2:
            q.print();
            break;
        case 3:
            try
            {
                cout << q.dequeue() << endl;
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