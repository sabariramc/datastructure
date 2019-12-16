#include "avl.h"
#include <iostream>
using namespace std;

void test_binarytree()
{
    AVL s;
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
            s.print();
            break;
        case 2:
            s.print();
            break;
        case 3:
            cin >> value;
            s.delete_node(value);
            break;
        case 4:
            return;
        default:
            break;
        }
    }
}