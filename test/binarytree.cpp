#include "redblack.h"
#include <iostream>
using namespace std;

void test_binarytree()
{
    RedBlack *s = new RedBlack();
    int instruction;
    int value;
    while (true)
    {
        cin >> instruction;
        switch (instruction)
        {
        case 1:
            cin >> value;
            s->insert_node(value);
            s->print();
            break;
        case 2:
            s->print();
            break;
        case 3:
            cin >> value;
            if (s->delete_node(value))
                s->print();
            break;
        case 4:
            s->test_tree_integraty();
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