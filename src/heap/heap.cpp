
#include "heap.h"

void Heap::heapify(int index)
{
    int left_child_index;
    int right_child_index;
    int swap_index;
    while (index < length)
    {
        left_child_index = index * 2 + 1;
        right_child_index = index * 2 + 2;
        swap_index = left_child_index;
        if (right_child_index < length && arr[left_child_index] > arr[right_child_index])
            swap_index = right_child_index;
        if (left_child_index >= length || arr[swap_index] > arr[index])
            break;
        swap(index, swap_index);
        index = swap_index;
    }
}

void Heap::add(int value)
{
    if (length + 1 >= capacity)
        reallocate(capacity == 0 ? 1 : capacity << 1);
    int index = length++;
    int parent_index = (index - 1) >> 1;
    int temp;
    arr[index] = value;
    while (index > 0 && arr[parent_index] > arr[index])
    {
        swap(index, parent_index);
        index = parent_index;
        parent_index = (index - 1) >> 1;
    }
}

int Heap::get()
{
    if (length <= 0)
        return -1;
    int temp = arr[0];
    arr[0] = arr[--length];
    heapify(0);
    return temp;
}

int Heap::peek()
{
    if (length == 0)
    {
        return -1;
    }
    return arr[0];
}

void Heap::swap(int idx_1, int idx_2)
{
    int temp = arr[idx_1];
    arr[idx_1] = arr[idx_2];
    arr[idx_2] = temp;
}

void Heap::reallocate(int capacity)
{
    int *temp = new int[capacity];
    this->capacity = capacity;
    for (int i = 0; i < length; i++)
        temp[i] = arr[i];
    delete[] arr;
    arr = temp;
}

void Heap::print()
{
    if (length <= 0)
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

bool Heap::test_integrity()
{
    return test_integrity(0, arr[0]);
}

bool Heap::test_integrity(int index, int value)
{
    if (length <= index)
        return true;
    bool val = test_integrity(index * 2 + 1, arr[index]) && test_integrity(index * 2 + 2, arr[index]);
    if (value > arr[index])
    {
        std::cout << "Error: Parent- " << value << " Child- " << arr[index] << std::endl;
        val = false;
    }
    return val;
}