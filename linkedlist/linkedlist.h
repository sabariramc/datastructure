class SinglyLinkedList{
    public:
        void insert_at_tail(int value);
        void insert_at_head(int value);
        int get_head();
        int get_tail();
        int peak_head();
        int peak_tail();
    private:
        int size = 0;
        struct Node{
            int value;
            Node* next;
            Node(int value){
                this->value = value;
                this->next = nullptr;

            }
            ~Node(){
                if (next != nullptr)
                {
                    delete(next);
                    next = nullptr;
                }
            }

        };
        Node *head = nullptr, *tail = nullptr;    
};