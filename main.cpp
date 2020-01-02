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
        FILE *x = freopen(argv[i], "r", stdin);
        cout << x << endl;
        if (x)
        {
            fflush(stdin);
            test_binarytree();
        }
        else
        {
            perror("File Error");
        }
        for (int i = 0; i < 1000; i++)
        {
            cout << "";
        }
    }
}
