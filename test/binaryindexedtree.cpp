#include "test.h"
#include "binaryindexedtree.h"
#include <iostream>
using namespace std;

void test_binaryindexedtree()
{
    int length;
    cin >> length;
    int a[length];
    for (int i = 0; i < length; i++)
        cin >> a[i];
    BinaryIndexedTree tree(a, length);
    tree.print();
    int command, val_1, val_2;
    while (true)
    {
        cin >> command;
        switch (command)
        {
        case 1:
            cin >> val_1;
            cout << "Prefix Sum[" << val_1 << "]:" << tree.prefix_query(val_1) << '\n';
            break;
        case 2:
            cin >> val_1 >> val_2;
            cout << "Range Sum[" << val_1 << "," << val_2 << "]:" << tree.range_query(val_1, val_2) << '\n';
            break;
        case 3:
            cin >> val_1 >> val_2;
            cout << "Set idx - " << val_1 << " value " << val_2 << '\n';
            tree.set(val_1, val_2);
            tree.print();
            break;
        case 4:
            tree.print();
            break;
        case 5:
            return;
        default:
            break;
        }
    }
}