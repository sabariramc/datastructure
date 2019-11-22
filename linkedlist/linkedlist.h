class DoublyLinkedList
{
public:
    void insert_at_tail(int value);
    void insert_at_head(int value);
    int get_head();
    int get_tail();
    int peak_head();
    int peak_tail();
    int get_size();

private:
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