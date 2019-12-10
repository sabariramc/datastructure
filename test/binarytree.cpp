#include "binarytree.h"
#include <iostream>
using namespace std;

void test_binarytree()
{
    binarytree s;
    int instruction;
    int value;
    while (true)
    {
        cin >> instruction;
        switch (instruction)
        {
        case 1:
            cin >> value;
            s.insert_node(value);
            break;
        case 2:
            s.print();
            break;
        case 4:
            return;
        default:
            break;
        }
    }
}