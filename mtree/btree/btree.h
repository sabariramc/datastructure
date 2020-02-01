class BTree
{
private:
    int key_size;
    const int min_key_requirement;

protected:
    struct Node
    {
        bool is_leaf;
        int no_of_key;
        int *value;
        Node **next_ptr;
        Node(int key_size)
        {
            is_leaf = true;
            no_of_key = 0;
            value = new int[key_size];
            next_ptr = new Node *[key_size + 1] { nullptr };
        }
        ~Node()
        {
            delete[] value;
            for (int i = 0; i <= no_of_key; i++)
            {
                delete next_ptr[i];
                next_ptr[i] = nullptr;
            }
            delete[] next_ptr;
            value = nullptr;
            next_ptr = nullptr;
        }
    };

public:
    bool insert_node(int value);
    bool delete_node(int value);
    int search_value(int value);
};