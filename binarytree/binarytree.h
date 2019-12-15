class BinaryTree
{
private:
    struct node
    {
        int value;
        node *left;
        node *right;
        node(int value)
        {
            this->value = value;
            left = nullptr;
            right = nullptr;
        }
        ~node()
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
    node *root;
    int size = 0;

public:
    BinaryTree();
    ~BinaryTree();
    void insert_node(int value);
    void print();
    void print_inorder(node *temp);
    void print_preorder(node *temp);
    void print_postorder(node *temp);
};
