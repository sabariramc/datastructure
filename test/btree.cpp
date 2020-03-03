#include "btree.h"
#include <iostream>
using namespace std;

void test_btree(int minimum_degree)
{
    BTree *s = new BTree(minimum_degree);
    int instruction;
    int value;
    while (true)
    {
        cin >> instruction;
        switch (instruction)
        {
        case 1:
            cin >> value;
            cout << "Insert: " << value << endl;
            s->add(value);
            s->print();
            s->test_integrity();
            break;
        case 2:
            s->print();
            break;
        case 3:
            cin >> value;
            cout << "Delete: " << value << endl;
            if (s->remove(value))
            {
                s->print();
                s->test_integrity();
            }
            break;
        case 4:
            s->test_integrity();
            break;
        case 5:
            return;
        case 6:
            cin >> value;
            {
                const int *ptr = s->search(value);
                if (ptr == nullptr)
                {
                    cout << "Value " << value << " not in tree\n";
                }
                else
                {
                    cout << "Value " << *ptr << " Found in tree\n";
                }
            }
            break;
        default:
            cout << "Invalid Instruction : " << instruction << endl;
            return;
        }
    }
}