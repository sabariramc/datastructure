#include <exception>
using namespace std;

class ListEmpty : public std::exception
{
public:
    virtual const char *what() const throw()
    {
        return "List is Empty";
    }
};
