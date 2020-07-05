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
    height = 0;
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
            return &(nav->key[target_index]);
        }
        nav = nav->next_ptr[target_index];
    }

    return nullptr;
}

bool BTree::add(int value)
{
    if (root->no_of_key == max_key_size)
    {
        Node *temp = new Node(max_key_size);
        temp->is_leaf = false;
        temp->next_ptr[0] = root;
        split_node(temp, 0);
        root = temp;
        height++;
    }
    bool flag = add_in_non_full_node(root, value);
    if (flag)
        size++;
    return flag;
}

bool BTree::remove(int value)
{
    Node *nav = root;
    bool need_search = true;
    int *search_result = nullptr;
    while (nav != nullptr)
    {
        if (need_search)
        {
            search_result = check_key(nav, value);
        }
        else
        {
            need_search = true;
        }
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
                    nav->key[key_index] = predecessor->key[replace_key_index];
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
                    nav->key[key_index] = successor->key[replace_key_index];
                    delete_key(successor, 0);
                }
                else
                {
                    int to_index = left->no_of_key;
                    *(search_result + 1) = to_index;
                    left->key[to_index++] = nav->key[key_index];
                    for (int i = 0; i < right->no_of_key; i++, to_index++)
                    {
                        left->key[to_index] = right->key[i];
                        left->next_ptr[to_index] = right->next_ptr[i];
                    }
                    left->next_ptr[to_index] = right->next_ptr[right->no_of_key];
                    left->no_of_key += right->no_of_key;
                    nav->next_ptr[key_index + 1] = nullptr;
                    for (int i = key_index; i < nav->no_of_key - 1; i++)
                    {
                        nav->key[i] = nav->key[i + 1];
                        nav->next_ptr[i + 1] = nav->next_ptr[i + 2];
                    }
                    nav->next_ptr[nav->no_of_key] = nullptr;
                    nav->no_of_key--;
                    if (nav == root && nav->no_of_key == 0)
                    {
                        root = left;
                        delete_node(nav);
                        height--;
                    }
                    delete_node(right);
                    nav = left;
                    need_search = false;
                    continue;
                }
            }
            size--;
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

    for (int i = 0; i < (min_key_requirement); i++)
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
    node_to_split->no_of_key = new_node->no_of_key = min_key_requirement;
    for (int i = nav->no_of_key; i > child_index; i--)
    {
        nav->next_ptr[i + 1] = nav->next_ptr[i];
        nav->key[i] = nav->key[i - 1];
    }
    nav->next_ptr[child_index + 1] = new_node;
    nav->key[child_index] = node_to_split->key[min_key_requirement];
    for (int i = node_to_split->no_of_key; i < max_key_size; i++)
    {
        node_to_split->key[i] = 0;
        node_to_split->next_ptr[i + 1] = nullptr;
    }
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
    int *key_check_result = check_key(nav, value);
    if (*key_check_result)
        return false;
    int i = nav->no_of_key - 1;
    for (; i >= 0 && nav->key[i] > value; i--)
    {
        nav->key[i + 1] = nav->key[i];
    }
    nav->key[i + 1] = value;
    nav->no_of_key++;
    return true;
}

BTree::Node *BTree ::decend(Node *nav, int next_ptr_index)
{
    if (nav->is_leaf)
        return nullptr;
    Node *decend_to_child = nav->next_ptr[next_ptr_index];
    if (decend_to_child->no_of_key >= minimum_degree)
        return decend_to_child;
    int left_sibiling_index = next_ptr_index - 1;
    int right_sibiling_index = next_ptr_index + 1;
    if (left_sibiling_index >= 0 && nav->next_ptr[left_sibiling_index]->no_of_key >= minimum_degree)
    {
        Node *left_sibiling = nav->next_ptr[left_sibiling_index];
        int key_from_sibiling = left_sibiling->key[left_sibiling->no_of_key - 1];
        Node *child_from_sibiling = left_sibiling->next_ptr[left_sibiling->no_of_key];
        left_sibiling->next_ptr[left_sibiling->no_of_key] = nullptr;
        left_sibiling->key[--left_sibiling->no_of_key] = 0;
        decend_to_child->next_ptr[decend_to_child->no_of_key + 1] = decend_to_child->next_ptr[decend_to_child->no_of_key];
        for (int i = decend_to_child->no_of_key; i > 0; i--)
        {
            decend_to_child->key[i] = decend_to_child->key[i - 1];
            decend_to_child->next_ptr[i] = decend_to_child->next_ptr[i - 1];
        }
        decend_to_child->next_ptr[0] = child_from_sibiling;
        decend_to_child->key[0] = nav->key[next_ptr_index - 1];
        decend_to_child->no_of_key++;
        nav->key[next_ptr_index - 1] = key_from_sibiling;
        return decend_to_child;
    }
    else if (right_sibiling_index <= nav->no_of_key && nav->next_ptr[right_sibiling_index]->no_of_key >= minimum_degree)
    {
        Node *right_sibiling = nav->next_ptr[right_sibiling_index];
        int key_from_sibiling = right_sibiling->key[0];
        Node *child_from_sibiling = right_sibiling->next_ptr[0];
        for (int i = 1; i < right_sibiling->no_of_key; i++)
        {
            right_sibiling->key[i - 1] = right_sibiling->key[i];
            right_sibiling->next_ptr[i - 1] = right_sibiling->next_ptr[i];
        }
        right_sibiling->next_ptr[right_sibiling->no_of_key - 1] = right_sibiling->next_ptr[right_sibiling->no_of_key];
        right_sibiling->next_ptr[right_sibiling->no_of_key] = nullptr;
        right_sibiling->key[--right_sibiling->no_of_key] = 0;
        decend_to_child->key[decend_to_child->no_of_key] = nav->key[next_ptr_index];
        decend_to_child->no_of_key++;
        decend_to_child->next_ptr[decend_to_child->no_of_key] = child_from_sibiling;
        nav->key[next_ptr_index] = key_from_sibiling;
        return decend_to_child;
    }
    else
    {
        Node *mearge_head = nullptr;
        Node *mearge_tail = nullptr;
        int key_to_decend_index = 0;
        if (left_sibiling_index >= 0)
        {
            mearge_tail = decend_to_child;
            mearge_head = nav->next_ptr[left_sibiling_index];
            key_to_decend_index = left_sibiling_index;
        }
        else
        {
            mearge_head = decend_to_child;
            mearge_tail = nav->next_ptr[right_sibiling_index];
            key_to_decend_index = right_sibiling_index - 1;
        }
        int &cnt = mearge_head->no_of_key;
        mearge_head->key[cnt++] = nav->key[key_to_decend_index];
        for (int i = 0; i < mearge_tail->no_of_key; i++, cnt++)
        {
            mearge_head->key[cnt] = mearge_tail->key[i];
            mearge_head->next_ptr[cnt] = mearge_tail->next_ptr[i];
        }
        mearge_head->next_ptr[cnt] = mearge_tail->next_ptr[mearge_tail->no_of_key];
        for (int i = key_to_decend_index; i <= nav->no_of_key; i++)
        {
            nav->key[i] = nav->key[i + 1];
            nav->next_ptr[i + 1] = nav->next_ptr[i + 2];
        }
        nav->next_ptr[nav->no_of_key--] = nullptr;
        if (nav == root && nav->no_of_key == 0)
        {
            root = mearge_head;
            delete_node(nav);
            height--;
        }
        delete_node(mearge_tail);
        return mearge_head;
    }
}

void BTree::delete_key(Node *nav, int index)
{
    for (int i = index; i < nav->no_of_key; i++)
    {
        nav->key[i] = nav->key[i + 1];
    }
    nav->key[--nav->no_of_key] = 0;
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
    vector<int> key = nav->key;
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
    cout << "Size:" << size << endl;
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
        {
            height_track.insert_node(height);
            cout << "Height:" << height << endl;
        }
        else if (height_track.search(height) == nullptr)
            return false;
        return true;
    }
    int i = 0;
    if (nav != root && nav->no_of_key < min_key_requirement)
    {
        cout << "ERROR: Min key requirement is violated at node that has starting key " << nav->key[0] << endl;
    }
    if (nav->no_of_key > max_key_size)
    {
        cout << "ERROR: Max key requirement is violated at node that has starting key " << nav->key[0] << endl;
    }
    for (; i < nav->no_of_key; i++)
    {
        bool height_property = test_properties(nav->next_ptr[i], height + 1, height_track, inorder_value);
        if (!height_property)
        {
            cout << "ERROR: Height property is violated for the branch that has the leaf node with starting key " << nav->key[0] << endl;
        }
        const int *value = inorder_value.peak();
        if (value != nullptr && *value >= nav->key[i])
        {
            cout << "ERROR: Key order property is violated at node that has starting key " << nav->key[0] << endl;
        }
        inorder_value.push(nav->key[i]);
    }
    test_properties(nav->next_ptr[i], height + 1, height_track, inorder_value);
    return true;
}