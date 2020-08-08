#include "indexedpriorityqueue.h"
#include "test.h"
#include <iostream>
using namespace std;

void test_indexedpriorityqueue()
{
    IndexedPriorityQueue h(200);
    int instruction;
    int value1, value2;
    while (true)
    {
        cin >> instruction;
        switch (instruction)
        {
        case 1:
            cin >> value1 >> value2;
            cout << "Add : key-" << value1 << " priority-" << value2 << endl;
            h.insert(value1, value2);
            h.print();
            h.test_integrity();
            break;
        case 2:
            cout << "Polled: " << h.poll() << endl;
            h.test_integrity();
            h.print();
            break;
        case 3:
            cout << "Peak: " << h.peek() << endl;
            break;
        case 4:
            cin >> value1 >> value2;
            cout << "Update : key-" << value1 << " priority-" << value2 << endl;
            h.update(value1, value2);
            h.print();
            h.test_integrity();
            break;
        case 5:
            cin >> value1;
            cout << "Remove : " << value1 << endl;
            h.remove(value1);
            h.print();
            h.test_integrity();
            break;
        case 6:
            return;
        default:
            break;
        }
    }
}
