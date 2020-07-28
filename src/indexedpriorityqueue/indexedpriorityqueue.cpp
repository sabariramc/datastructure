#include "indexedpriorityqueue.h"

IndexedPriorityQueue::IndexedPriorityQueue(int capacity)
{
    this->capacity = capacity;
    priority = new int[capacity];
    pm = new int[capacity];
    im = new int[capacity];
    for (int i = 0; i < capacity; i++)
    {
        priority[i] = -1;
        pm[i] = -1;
        im[i] = -1;
    }
}

IndexedPriorityQueue::~IndexedPriorityQueue()
{
    delete[] priority;
    delete[] pm;
    delete[] im;
    std::cout << "Destructor\n";
}

void IndexedPriorityQueue::swap(int i, int j)
{
    pm[im[i]] = j;
    pm[im[j]] = i;
    int temp = im[i];
    im[i] = im[j];
    im[j] = temp;
}

void IndexedPriorityQueue::swim(int i)
{
    while (i > 0)
    {
        int parent = (i - 1) >> 1;
        if (priority[im[i]] < priority[im[parent]])
            swap(parent, i);
        i = parent;
    }
}

void IndexedPriorityQueue::sink(int i)
{
    int left, right, swap_index;
    while (i < size)
    {
        left = (i << 1) + 1;
        right = (i << 1) + 2;
        swap_index = left;
        if (right < size && priority[im[right]] < priority[im[left]])
            swap_index = right;
        if (left >= size || priority[im[swap_index]] > priority[im[i]])
            break;
        swap(i, swap_index);
        i = swap_index;
    }
}

void IndexedPriorityQueue::insert(int key, int priority)
{
    if (size >= capacity || key < 0 || key >= capacity || pm[key] != -1)
        return;
    this->priority[size] = priority;
    pm[key] = size;
    im[size] = key;
    swim(size);
    size++;
}

int IndexedPriorityQueue::poll()
{
    if (size <= 0)
    {
        return -1;
    }
    int key = im[0];
    pm[key] = -1;
    priority[key] = -1;
    swap(0, size--);
    sink(0);
    im[size] = -1;
    return key;
}

void IndexedPriorityQueue::update(int key, int priority)
{
    if (key >= capacity || key < 0 || this->pm[key] == -1)
        return;
    int diff = priority - this->priority[key];
    if (diff < 0)
    {
        decrease(key, -diff);
    }
    else if (diff > 0)
    {
        increase(key, diff);
    }
}

void IndexedPriorityQueue::increase(int key, int value)
{
    if (value <= 0 || key >= capacity || key < 0 || pm[key] == -1)
        return;
    priority[key] += value;
    sink(pm[key]);
}

void IndexedPriorityQueue::decrease(int key, int value)
{
    if (value <= 0 || key >= capacity || key < 0 || pm[key] == -1)
        return;
    priority[key] -= value;
    swim(pm[key]);
}

void IndexedPriorityQueue::remove(int key)
{
    if (key >= capacity || key < 0 || this->pm[key] == -1)
        return;
    int pos = pm[key];
    priority[key] = -1;
    pm[key] = -1;
    if (pos != size - 1)
    {
        swap(pos, size--);
        sink(pos);
        swim(pos);
    }
    im[size] = -1;
}

int IndexedPriorityQueue::peek()
{
    if (size <= 0)
    {
        return -1;
    }
    return im[0];
}

void IndexedPriorityQueue::print()
{
    if (size <= 0)
    {
        std::cout << "[]\n";
    }
    else
    {
        std::cout << "[ " << priority[im[0]];
        for (int i = 1; i < size; i++)
        {
            std::cout << ", " << priority[im[i]];
        }
        std::cout << " ]\n";
    }
}

bool IndexedPriorityQueue::test_integrity()
{
    return test_integrity(0, priority[im[0]]);
}

bool IndexedPriorityQueue::test_integrity(int index, int value)
{
    if (size <= index)
        return true;
    bool val = test_integrity(index * 2 + 1, priority[im[index]]) && test_integrity(index * 2 + 2, priority[im[index]]);
    if (value > priority[im[index]])
    {
        std::cout << "Error: Parent- " << value << " Child- " << priority[im[index]] << '\n';
        val = false;
    }
    return val;
}