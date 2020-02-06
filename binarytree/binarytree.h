
#ifndef BINARYTREE_H
#define BINARYTREE_H
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
    virtual void delete_node(Node *node);
    virtual void print_node(Node *node);

public:
    BinaryTree();
    ~BinaryTree();
    virtual bool insert_node(int value);
    virtual bool delete_node(int value);
    virtual void print() final;
    virtual void print_inorder(Node *temp);
    virtual void print_preorder(Node *temp);
    virtual void print_postorder(Node *temp);
};

#endif // !BINARYTREE_H
