#include <exception>

class ListEmpty : std::exception
{
public:
    virtual const char *what() const throw()
    {
        char a[14] = "List is Empty";
        return a;
    }
};
