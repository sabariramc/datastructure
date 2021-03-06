#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class DoublyLinkedList
{
public:
    void insert_at_tail(int value);
    void insert_at_head(int value);
    int get_head();
    int get_tail();
    const int *peak_head();
    const int *peak_tail();
    int get_size();
    void print();
    DoublyLinkedList()
    {
    }
    ~DoublyLinkedList()
    {
        delete (head);
        head = nullptr;
        tail = nullptr;
    }

private:
    const static int position_head = 1;
    const static int position_tail = -1;
    int size = 0;
    void initiate_list(int value);
    void insert(int value, int position);
    int get(int position);
    int peak(int position);
    void terminate_list();
    struct Node
    {
        int value;
        Node *next;
        Node *prev;
        Node(int value)
        {
            this->value = value;
            this->next = nullptr;
            this->prev = nullptr;
        }
        ~Node()
        {
            prev = nullptr;
            if (next != nullptr)
            {
                delete (next);
                next = nullptr;
            }
        }
    };
    Node *head = nullptr, *tail = nullptr;
};

#endif /*LINKEDLIST_H*/