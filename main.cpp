#include <exception>
#include <iostream>

using namespace std;

#include "test.h"

int main(int argc, const char **argv)
{
    freopen("output.txt", "w", stdout);
    for (int i = 1; i < argc; i++)
    {
        cout << argv[i] << endl;
        freopen(argv[i], "r", stdin);
        test_binarytree();
    }
}
