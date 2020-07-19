#include <exception>
#include <iostream>

using namespace std;

#include "test.h"

int main(int argc, const char **argv)
{
    freopen("output/output.txt", "w", stdout);
    freopen("testcases/input.txt", "r", stdin);
    test_binaryindexedtree();
    // freopen("error.txt", "w", stderr);
    // for (int i = 1; i < argc; i++)
    // {
    //     cout << argv[i] << endl;
    //     FILE *x =
    //     cout << x << endl;
    //     if (x)
    //     {
    //         fflush(stdin);
    //         test_binarytree();
    //     }
    //     else
    //     {
    //         perror("File Error");
    //     }
    //     for (int i = 0; i < 1000; i++)
    //     {
    //         cout << "";
    //     }
    // }
    cout << "TEST ENDED";
}
