#include <iostream>
using namespace std;
#include "btree.h"

BTree::BTree(int minimum_degree) : minimum_degree(minimum_degree), max_key_size((2 * minimum_degree) - 1), min_key_requirement(minimum_degree - 1)
{
    if (minimum_degree < 2)
    {
        throw "Minimum degree cannot be less than 2";
    }
    root = new Node(max_key_size);
    size = 0;
}

BTree::~BTree()
{
    delete root;
    root = nullptr;
}

const int *BTree::search(int value)
{
    Node *nav = root;
    while (nav != nullptr)
    {
        int *search_result = check_key(nav, value);
        int target_index = *(search_result + 1);
        if (*search_result == 1)
        {
            return nav->key + target_index;
        }
        nav = nav->next_ptr[target_index];
    }

    return nullptr;
}

bool BTree::add(int value)
{
    cout << "Insert: " << value << endl;
    Node *nav = root;
    if (nav->no_of_key == max_key_size)
    {
        Node *temp = new Node(max_key_size);
        root = temp;
        temp->is_leaf = false;
        temp->next_ptr[0] = nav;
        split_node(temp, 0);
    }
    bool flag = add_in_non_full_node(root, value);
    if (flag)
        size++;
    return flag;
}

bool BTree::remove(int value)
{
    Node *nav = root;
    while (nav != nullptr)
    {
        int *search_result = check_key(nav, value);
        if (*search_result == 1)
        {
            int key_index = *(search_result + 1);
            if (nav->is_leaf)
            {
                delete_key(nav, key_index);
            }
            else
            {
                Node *left = nav->next_ptr[key_index];
                Node *right = nav->next_ptr[key_index + 1];
                if (left->no_of_key >= minimum_degree)
                {
                    Node *predecessor = left;
                    while (predecessor->is_leaf == false)
                    {
                        predecessor = decend(predecessor, predecessor->no_of_key);
                    }
                    int replace_key_index = predecessor->no_of_key - 1;
                    nav[key_index] = predecessor->key[replace_key_index];
                    delete_key(predecessor, replace_key_index);
                }
                else if (right->no_of_key >= minimum_degree)
                {
                    Node *successor = right;
                    while (successor->is_leaf == false)
                    {
                        successor = decend(successor, 0);
                    }
                    int replace_key_index = 0;
                    nav[key_index] = successor->key[replace_key_index];
                    delete_key(successor, 0);
                }
                else
                {
                    int from_index = left->no_of_key;
                    left->key[from_index++] = nav->key[key_index];
                    for (int i = 0; i < right->no_of_key; i++, from_index++)
                    {
                        left->key[from_index] = right->key[i];
                        left->next_ptr[from_index] = right->next_ptr[i];
                    }
                    left->next_ptr[from_index] = right->next_ptr[right->no_of_key];
                    left->no_of_key += right->no_of_key;
                    nav->next_ptr[key_index + 1] = nullptr;
                    for (int i = key_index; i < nav->no_of_key - 1; i++)
                    {
                        nav->key[i] = nav->key[i + 1];
                        nav->next_ptr[i + 1] = nav->next_ptr[i + 2];
                    }
                    nav->no_of_key--;
                    nav->next_ptr[nav->no_of_key] = nullptr;
                    if (nav == root && nav->no_of_key == 0)
                    {
                        root = left;
                        delete_node(nav);
                    }
                    delete_node(right);
                    nav = left;
                    continue;
                }
            }
            return true;
        }
        else
        {
            int next_child_idx = *(search_result + 1);
            nav = decend(nav, next_child_idx);
        }
    }
    return false;
}

void BTree::split_node(Node *nav, int child_index)
{
    Node *new_node = new Node(max_key_size);
    Node *node_to_split = nav->next_ptr[child_index];
    new_node->is_leaf = node_to_split->is_leaf;
    new_node->no_of_key = minimum_degree - 1;
    for (int i = 0; i < (minimum_degree - 1); i++)
    {
        new_node->key[i] = node_to_split->key[minimum_degree + i];
    }
    if (!node_to_split->is_leaf)
    {
        for (int i = 0; i < minimum_degree; i++)
        {
            new_node->next_ptr[i] = node_to_split->next_ptr[minimum_degree + i];
        }
    }
    node_to_split->no_of_key = minimum_degree - 1;
    for (int i = nav->no_of_key; i > child_index; i--)
    {
        nav->next_ptr[i + 1] = nav->next_ptr[i];
    }
    nav->next_ptr[child_index + 1] = new_node;
    for (int i = nav->no_of_key - 1; i >= child_index; i--)
    {
        nav->key[i + 1] = nav->key[i];
    }
    nav->key[child_index] = node_to_split->key[minimum_degree - 1];
    nav->no_of_key++;
}

bool BTree::add_in_non_full_node(Node *nav, int value)
{
    int no_of_keys = nav->no_of_key;
    while (!(nav->is_leaf))
    {
        int *search_result = check_key(nav, value);
        if (*search_result == 1)
        {
            return false;
        }
        int next_ptr_index = *(search_result + 1);
        if (nav->next_ptr[next_ptr_index]->no_of_key == max_key_size)
        {
            split_node(nav, next_ptr_index);
            if (value > nav->key[next_ptr_index])
            {
                next_ptr_index++;
            }
        }
        nav = nav->next_ptr[next_ptr_index];
    }
    int i = nav->no_of_key - 1;
    if (check_key(nav, value))
        return false;
    for (; i >= 0 && nav->key[i] > value; i--)
    {
        nav->key[i + 1] = nav->key[i];
    }
    nav->key[i + 1] = value;
    nav->no_of_key++;
    return true;
}

void BTree::delete_key(Node *nav, int index)
{
    for (int i = index; i < nav->no_of_key; i++)
    {
        nav->key[i] = i + 1;
    }
    nav->no_of_key--;
}

void BTree::delete_node(Node *nav)
{
    for (int i = 0; i <= nav->no_of_key; i++)
    {
        nav->next_ptr[i] = nullptr;
    }
    delete (nav);
}

int *BTree::check_key(Node *nav, int value)
{
    int start = 0;
    int end = nav->no_of_key - 1;
    int next_ptr_index;
    int *key = nav->key;
    int *result = new int[2]{0};
    while (start <= end)
    {
        int diff = end - start;
        int mid = (start + end) / 2;
        if (key[mid] == value)
        {
            result[0] = 1;
            result[1] = mid;
            return result;
        }
        else if (diff <= 1)
        {
            if (value < key[start])
                next_ptr_index = start;
            else if (value > key[end])
                next_ptr_index = end + 1;
            else if (value == key[end])
            {
                result[0] = 1;
                result[1] = end;
                return result;
            }
            else
                next_ptr_index = end;
            break;
        }
        else if (key[mid] > value)
        {
            end = mid;
        }
        else
        {
            start = mid;
        }
    }
    result[0] = 0;
    result[1] = next_ptr_index;
    return result;
}

void BTree::print()
{
    cout << "In-order traversal:";
    print_inorder(root);
    cout << endl;
    cout << "Pre-order traversal:";
    print_preorder(root);
    cout << endl;
}

void BTree::print_inorder(Node *nav)
{
    if (nav == nullptr)
    {
        return;
    }
    int i = 0;
    for (; i < nav->no_of_key; i++)
    {
        print_inorder(nav->next_ptr[i]);
        cout << nav->key[i] << " ";
    }
    print_inorder(nav->next_ptr[i]);
}

void BTree::print_preorder(Node *nav)
{
    if (nav == nullptr)
    {
        return;
    }
    int i = 0;
    for (; i < nav->no_of_key; i++)
    {
        cout << nav->key[i] << " ";
        print_preorder(nav->next_ptr[i]);
    }
    print_preorder(nav->next_ptr[i]);
}

bool BTree::test_integrity()
{
    Stack inorder_value;
    RedBlack height_track;
    test_properties(root, 0, height_track, inorder_value);
}

bool BTree::test_properties(Node *nav, int height, RedBlack &height_track, Stack &inorder_value)
{
    if (nav == nullptr)
    {
        if (height_track.get_size() == 0)
            height_track.insert_node(height);
        else if (height_track.search(height) == nullptr)
            return false;
        return true;
    }
    int i = 0;
    if (nav != root && nav->no_of_key < min_key_requirement)
    {
        cout << "Min key requirement is violated at node that has starting key " << nav->key[0] << endl;
    }
    if (nav->no_of_key > max_key_size)
    {
        cout << "Max key requirement is violated at node that has starting key " << nav->key[0] << endl;
    }
    for (; i < nav->no_of_key; i++)
    {
        bool height_property = test_properties(nav->next_ptr[i], height + 1, height_track, inorder_value);
        if (!height_property)
        {
            cout << "Height property is violated for the branch that has the leaf node with starting key " << nav->key[0] << endl;
        }
        const int *value = inorder_value.peak();
        if (value != nullptr && *value > nav->key[i])
        {
            cout << "Key order property is violated at node that has starting key " << nav->key[0] << endl;
        }
        inorder_value.push(nav->key[i]);
    }
    test_properties(nav->next_ptr[i], height + 1, height_track, inorder_value);
    return true;
}