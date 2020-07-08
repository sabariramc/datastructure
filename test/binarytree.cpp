// #include "redblack.h"
#include "bst.h"
#include <iostream>
using namespace std;

void test_binarytree()
{
    BST *s = new BST();
    int instruction;
    int value;
    while (true)
    {
        cin >> instruction;
        switch (instruction)
        {
        case 1:
            cin >> value;
            cout << "Insert:" << value << "\n";
            if (s->insert_node(value)){
                s->print();
            s->test_tree_integraty();}
            break;
        case 2:
            s->print();
            break;
        case 3:
            cin >> value;
            cout << "Delete:" << value << "\n";
            if (s->delete_node(value))
            {
                cout << "Value deleted from the tree\n";
                s->print();
                s->test_tree_integraty();
            }
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