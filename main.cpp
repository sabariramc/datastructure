#include <exception>
#include <iostream>

using namespace std;

#include "test.h"

int main(int argc, const char **argv)
{
    fclose(stdin);
    freopen(argv[1], "r", stdin);
    test_binarytree();
}
