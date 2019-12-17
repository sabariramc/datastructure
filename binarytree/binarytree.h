class BinaryTree
{
protected:
    struct Node
    {
        int value;
        Node *left;
        Node *right;
        Node(int value)
        {
            this->value = value;
            left = nullptr;
            right = nullptr;
        }
        ~Node()
        {
            if (left != nullptr)
            {
                delete (left);
                left = nullptr;
            }
            if (right != nullptr)
            {
                delete (right);
                right = nullptr;
            }
        }
    };
    Node *root;
    int size = 0;
    bool delete_node(Node **temp, int value);
    void delete_node(Node *node);

public:
    BinaryTree();
    ~BinaryTree();
    void insert_node(int value);
    bool delete_node(int value);
    void print();
    void print_inorder(Node *temp);
    void print_preorder(Node *temp);
    void print_postorder(Node *temp);
};
