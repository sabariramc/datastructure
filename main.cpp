#include <exception>
#include <iostream>

using namespace std;

#include "test.h"

int main(int argc, const char **argv)
{
    fclose(stdin);
    freopen("input.txt", "r", stdin);
    test_binarytree();
}
