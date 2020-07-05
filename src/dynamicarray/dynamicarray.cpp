#include <iostream>
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

template <class T>
class DynamicArray
{
private:
    int capacity = 0;
    int length = 0;
    T *arr;

public:
    DynamicArray() : DynamicArray(16) { length = 0; };
    DynamicArray(int capacity)
    {
        if (capacity < 0)
        {
            throw "Capacity cant be less than 0";
        }
        length = this->capacity = capacity;
        if (length > 0)
            arr = new T[length];
        else
        {
            arr = nullptr;
        }
    };
    DynamicArray(int capacity, T init_value) : DynamicArray(capacity)
    {
        for (int i = 0; i < length; i++)
            arr[i] = init_value;
    };
    ~DynamicArray()
    {
        length = capacity = 0;
        delete[] arr;
        arr = nullptr;
    }

    int size();
    int getCapacity();
    bool is_empty();
    T &operator[](int index);
    void clear();
    void add(T value);
    void remove_at(int index);
    void print();
};

template <class T>
int DynamicArray<T>::size()
{
    return length;
}

template <class T>
bool DynamicArray<T>::is_empty()
{
    return size() == 0;
}

template <class T>
T &DynamicArray<T>::operator[](int index)
{
    if (index < 0 || index >= length)
    {
        throw "Index out of bound";
    }
    return arr[index];
}

template <class T>
void DynamicArray<T>::clear()
{
    length = 0;
}

template <class T>
void DynamicArray<T>::add(T value)
{
    if (length + 1 >= capacity)
    {
        if (capacity == 0)
            capacity = 1;
        else
        {
            capacity <<= 1;
        }
        T *temp = new T[capacity];
        for (int i = 0; i < length; i++)
        {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }
    arr[length++] = value;
}

template <class T>
void DynamicArray<T>::remove_at(int index)
{
    if (index < 0 || index >= length)
    {
        throw "Index out of bound";
    }
    for (int i = index; i < length; i++)
    {
        arr[i] = arr[i + 1];
    }
    length--;
}

template <class T>
void DynamicArray<T>::print()
{
    if (length == 0)
    {
        std::cout << "[]\n";
    }
    else
    {
        std::cout << "[ " << arr[0];
        for (int i = 1; i < length; i++)
        {
            std::cout << ", " << arr[i];
        }
        std::cout << " ]\n";
    }
}

#endif // !DYNAMIC_ARRAY_H