#include "bplustree.h"
#include <iostream>
using namespace std;

const int MAX = 26;

// Returns a string of random alphabets of
// length n.
string get_random_string(int n)
{
    char alphabet[MAX] = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z'};

    string res = "";
    for (int i = 0; i < n; i++)
        res = res + alphabet[rand() % MAX];

    return res;
};

void test_bplustree(int minimum_degree)
{
    BPlusTree *s = new BPlusTree(minimum_degree);
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
            s->add(value, get_random_string(value % 100));
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
                const string *ptr = s->search(value);
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