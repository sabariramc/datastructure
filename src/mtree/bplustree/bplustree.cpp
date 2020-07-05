#include <iostream>
using namespace std;
#include "bplustree.h"

BPlusTree::BPlusTree(int minimum_degree) : minimum_degree(minimum_degree), max_key_size((2 * minimum_degree) - 1), min_key_requirement(minimum_degree - 1)
{
    if (minimum_degree < 2)
    {
        throw "Minimum degree cannot be less than 2";
    }
    root = Node::get_new_leaf_node(max_key_size);
    size = 0;
    height = 0;
}

BPlusTree::~BPlusTree()
{
    delete root;
    root = nullptr;
}

const string *BPlusTree::search(int value)
{
    Node *nav = root;
    while (nav != nullptr)
    {
        int *search_result = check_key(nav, value);
        int target_index = *(search_result + 1);
        if (*search_result == 1)
        {
            return nav->data_ptr[target_index];
        }
        nav = nav->next_ptr[target_index];
    }

    return nullptr;
}

bool BPlusTree::add(int key, string value)
{
    if (root->no_of_key == max_key_size)
    {
        Node *temp = Node::get_new_internal_node(max_key_size);
        temp->next_ptr[0] = root;
        split_node(temp, 0);
        root = temp;
        height++;
    }
    bool flag = add_in_non_full_node(root, key, &value);
    if (flag)
        size++;
    return flag;
}

bool BPlusTree::remove(int value)
{
    Node *nav = root;
    int *search_result = nullptr;
    vector<Node *> path_stack;
    vector<int> path_index;
    while (nav != nullptr)
    {
        search_result = check_key(nav, value);
        if (*search_result == 1)
        {
            int key_index = *(search_result + 1);
            delete_key(nav, key_index);
            int parent_index = path_stack.size() - 1;
            while (nav != root && nav->no_of_key < min_key_requirement)
            {
                Node *rebalance_child = nav;
                nav = path_stack[parent_index];
                int next_ptr_index = path_index[parent_index--];
                int left_sibiling_index = next_ptr_index - 1;
                int right_sibiling_index = next_ptr_index + 1;
                if (left_sibiling_index >= 0 && nav->next_ptr[left_sibiling_index]->no_of_key >= minimum_degree)
                {
                    Node *left_sibiling = nav->next_ptr[left_sibiling_index];
                    int key_from_sibiling = left_sibiling->key[left_sibiling->no_of_key - 1];
                    if (rebalance_child->is_leaf)
                    {
                        for (int i = rebalance_child->no_of_key; i > 0; i--)
                        {
                            rebalance_child->key[i] = rebalance_child->key[i - 1];
                            rebalance_child->data_ptr[i] = rebalance_child->data_ptr[i - 1];
                        }
                        rebalance_child->key[0] = left_sibiling->key[left_sibiling->no_of_key - 1];
                        rebalance_child->data_ptr[0] = left_sibiling->data_ptr[left_sibiling->no_of_key - 1];
                        key_from_sibiling = left_sibiling->key[left_sibiling->no_of_key - 2];
                        left_sibiling->data_ptr[left_sibiling->no_of_key - 1] = nullptr;
                    }
                    else
                    {
                        rebalance_child->next_ptr[rebalance_child->no_of_key + 1] = rebalance_child->next_ptr[rebalance_child->no_of_key];
                        for (int i = rebalance_child->no_of_key; i > 0; i--)
                        {
                            rebalance_child->key[i] = rebalance_child->key[i - 1];
                            rebalance_child->next_ptr[i] = rebalance_child->next_ptr[i - 1];
                        }
                        rebalance_child->next_ptr[0] = left_sibiling->next_ptr[left_sibiling->no_of_key];
                        rebalance_child->key[0] = nav->key[next_ptr_index - 1];
                        left_sibiling->next_ptr[left_sibiling->no_of_key] = nullptr;
                    }
                    rebalance_child->no_of_key++;
                    left_sibiling->key[--left_sibiling->no_of_key] = 0;
                    nav->key[next_ptr_index - 1] = key_from_sibiling;
                }
                else if (right_sibiling_index <= nav->no_of_key && nav->next_ptr[right_sibiling_index]->no_of_key >= minimum_degree)
                {
                    Node *right_sibiling = nav->next_ptr[right_sibiling_index];
                    int key_from_sibiling = right_sibiling->key[0];
                    if (rebalance_child->is_leaf)
                    {
                        rebalance_child->data_ptr[rebalance_child->no_of_key] = right_sibiling->data_ptr[0];
                        rebalance_child->key[rebalance_child->no_of_key] = right_sibiling->key[0];
                        for (int i = 1; i < right_sibiling->no_of_key; i++)
                        {
                            right_sibiling->key[i - 1] = right_sibiling->key[i];
                            right_sibiling->data_ptr[i - 1] = right_sibiling->data_ptr[i];
                        }
                        right_sibiling->data_ptr[right_sibiling->no_of_key - 1] = nullptr;
                    }
                    else
                    {
                        Node *child_from_sibiling = right_sibiling->next_ptr[0];
                        for (int i = 1; i < right_sibiling->no_of_key; i++)
                        {
                            right_sibiling->key[i - 1] = right_sibiling->key[i];
                            right_sibiling->next_ptr[i - 1] = right_sibiling->next_ptr[i];
                        }
                        right_sibiling->next_ptr[right_sibiling->no_of_key - 1] = right_sibiling->next_ptr[right_sibiling->no_of_key];
                        right_sibiling->next_ptr[right_sibiling->no_of_key] = nullptr;
                        rebalance_child->key[rebalance_child->no_of_key] = nav->key[next_ptr_index];
                        rebalance_child->next_ptr[rebalance_child->no_of_key + 1] = child_from_sibiling;
                    }
                    nav->key[next_ptr_index] = key_from_sibiling;
                    right_sibiling->key[--right_sibiling->no_of_key] = 0;
                    rebalance_child->no_of_key++;
                }
                else
                {
                    Node *mearge_head = nullptr;
                    Node *mearge_tail = nullptr;
                    int key_to_decend_index = 0;
                    if (left_sibiling_index >= 0)
                    {
                        mearge_tail = rebalance_child;
                        mearge_head = nav->next_ptr[left_sibiling_index];
                        key_to_decend_index = left_sibiling_index;
                    }
                    else
                    {
                        mearge_head = rebalance_child;
                        mearge_tail = nav->next_ptr[right_sibiling_index];
                        key_to_decend_index = right_sibiling_index - 1;
                    }
                    int &cnt = mearge_head->no_of_key;
                    if (mearge_head->is_leaf)
                    {
                        for (int i = 0; i < mearge_tail->no_of_key; i++, cnt++)
                        {
                            mearge_head->key[cnt] = mearge_tail->key[i];
                            mearge_head->data_ptr[cnt] = mearge_tail->data_ptr[i];
                        }
                        mearge_head->adjusant_ptr = mearge_tail->adjusant_ptr;
                    }
                    else
                    {
                        mearge_head->key[cnt++] = nav->key[key_to_decend_index];
                        for (int i = 0; i < mearge_tail->no_of_key; i++, cnt++)
                        {
                            mearge_head->key[cnt] = mearge_tail->key[i];
                            mearge_head->next_ptr[cnt] = mearge_tail->next_ptr[i];
                        }
                        mearge_head->next_ptr[cnt] = mearge_tail->next_ptr[mearge_tail->no_of_key];
                    }
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
                }
            }
            size--;
            return true;
        }
        int next_child_idx = *(search_result + 1);
        path_stack.push_back(nav);
        path_index.push_back(next_child_idx);
        if (nav->is_leaf)
        {
            nav = nullptr;
        }
        else
        {
            nav = nav->next_ptr[next_child_idx];
        }
    }
    return false;
}

void BPlusTree::split_node(Node *nav, int child_index)
{
    Node *new_node = nullptr;
    Node *node_to_split = nav->next_ptr[child_index];
    if (node_to_split->is_leaf)
    {
        new_node = Node::get_new_leaf_node(max_key_size);
        new_node->adjusant_ptr = node_to_split->adjusant_ptr;
        node_to_split->adjusant_ptr = new_node;
        for (int i = 0; i < (min_key_requirement); i++)
        {
            new_node->key[i] = node_to_split->key[minimum_degree + i];
            new_node->data_ptr[i] = node_to_split->data_ptr[minimum_degree + i];
            node_to_split->key[minimum_degree + i] = 0;
            node_to_split->data_ptr[minimum_degree + i] = nullptr;
        }
        node_to_split->no_of_key = minimum_degree;
        new_node->no_of_key = min_key_requirement;
    }
    else
    {
        new_node = Node::get_new_internal_node(max_key_size);
        for (int i = 0; i < (min_key_requirement); i++)
        {
            new_node->key[i] = node_to_split->key[minimum_degree + i];
            new_node->next_ptr[i] = node_to_split->next_ptr[minimum_degree + i];
            node_to_split->key[minimum_degree + i] = 0;
            node_to_split->next_ptr[minimum_degree + i] = nullptr;
        }
        new_node->next_ptr[min_key_requirement] = node_to_split->next_ptr[node_to_split->no_of_key];
        node_to_split->next_ptr[node_to_split->no_of_key] = nullptr;
        node_to_split->no_of_key = new_node->no_of_key = min_key_requirement;
    }
    for (int i = nav->no_of_key; i > child_index; i--)
    {
        nav->next_ptr[i + 1] = nav->next_ptr[i];
        nav->key[i] = nav->key[i - 1];
    }
    nav->next_ptr[child_index + 1] = new_node;
    nav->key[child_index] = node_to_split->key[min_key_requirement];
    if (!node_to_split->is_leaf)
    {
        node_to_split->key[min_key_requirement] = 0;
    }
    nav->no_of_key++;
}

bool BPlusTree::add_in_non_full_node(Node *nav, int key, string *value)
{
    int no_of_keys = nav->no_of_key;
    while (!(nav->is_leaf))
    {
        int *search_result = check_key(nav, key);
        int next_ptr_index = *(search_result + 1);
        if (nav->next_ptr[next_ptr_index]->no_of_key == max_key_size)
        {
            split_node(nav, next_ptr_index);
            if (key > nav->key[next_ptr_index])
            {
                next_ptr_index++;
            }
        }
        nav = nav->next_ptr[next_ptr_index];
    }
    int *key_check_result = check_key(nav, key);
    if (*key_check_result)
        return false;
    int i = nav->no_of_key - 1;
    for (; i >= 0 && nav->key[i] > key; i--)
    {
        nav->key[i + 1] = nav->key[i];
        nav->data_ptr[i + 1] = nav->data_ptr[i];
    }
    nav->key[i + 1] = key;
    nav->data_ptr[i + 1] = value;
    nav->no_of_key++;
    return true;
}

void BPlusTree::delete_key(Node *nav, int index)
{
    for (int i = index; i < nav->no_of_key; i++)
    {
        nav->key[i] = nav->key[i + 1];
        nav->data_ptr[i] = nav->data_ptr[i + 1];
    }
    nav->key[--nav->no_of_key] = 0;
    nav->data_ptr[nav->no_of_key] = nullptr;
}

void BPlusTree::delete_node(Node *nav)
{
    if (nav->is_leaf)
    {
        for (int i = 0; i < nav->no_of_key; i++)
        {
            nav->data_ptr[i] = nullptr;
        }
    }
    else
    {
        for (int i = 0; i <= nav->no_of_key; i++)
        {
            nav->next_ptr[i] = nullptr;
        }
    }
    nav->adjusant_ptr = nullptr;
    delete (nav);
}

int *BPlusTree::check_key(Node *nav, const int value)
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
            if (nav->is_leaf)
            {
                result[0] = 1;
            }
            else
            {
                result[0] = 0;
            }
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
                if (nav->is_leaf)
                {
                    result[0] = 1;
                }
                else
                {
                    result[0] = 0;
                }
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

void BPlusTree::print()
{
    cout << "Size:" << size << endl;
    cout << "In-order traversal:";
    print_inorder(root);
    cout << endl;
    cout << "Pre-order traversal:";
    print_preorder(root);
    cout << endl;
}

void BPlusTree::print_inorder(Node *nav)
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

void BPlusTree::print_preorder(Node *nav)
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

bool BPlusTree::test_integrity()
{
    Stack inorder_value, internal_node_track;
    RedBlack height_track, leaf_key_track;
    test_properties(root, 0, height_track, inorder_value, leaf_key_track, internal_node_track);
    Node *temp = root;
    while (!temp->is_leaf)
    {
        temp = temp->next_ptr[0];
    }
    int leaf_count = 0;
    while (temp != nullptr)
    {
        leaf_count += temp->no_of_key;
        for (int i = 0; i < temp->no_of_key; i++)
        {
            if (leaf_key_track.search(temp->key[i]) == nullptr)
            {
                cout << "ERROR: Leaf key conflict at key " << temp->key[i] << endl;
            }
        }
        temp = temp->adjusant_ptr;
    }
    if (leaf_count != leaf_key_track.get_size())
    {
        cout << "ERROR: Leaf key count mismatch" << endl;
    }
}

bool BPlusTree::test_properties(Node *nav, int height, RedBlack &height_track, Stack &inorder_value, RedBlack &leaf_key_track, Stack &internal_node_track)
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
    if (nav->is_leaf)
    {
        for (int i = 0; i < nav->no_of_key; i++)
        {
            if (!leaf_key_track.insert_node(nav->key[i]))
            {
                cout << "ERROR: Duplicate leaf key at " << nav->key[i] << endl;
            }
        }
    }

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
        bool height_property = test_properties(nav->next_ptr[i], height + 1, height_track, inorder_value, leaf_key_track, internal_node_track);
        if (!height_property)
        {
            cout << "ERROR: Height property is violated for the branch that has the leaf node at key " << nav->key[i] << endl;
        }
        const int *value = inorder_value.peak();
        if (value != nullptr && *value > nav->key[i])
        {
            cout << "ERROR: Inorder key order property is violated at node of key " << nav->key[i] << endl;
        }

        inorder_value.push(nav->key[i]);
        if (!nav->is_leaf)
        {
            const int *in_value = internal_node_track.peak();
            if (in_value != nullptr && *in_value >= nav->key[i])
            {
                cout << "ERROR: Internal key order property is violated at node of key " << nav->key[i] << endl;
            }
            internal_node_track.push(nav->key[i]);
        }
    }
    test_properties(nav->next_ptr[i], height + 1, height_track, inorder_value, leaf_key_track, internal_node_track);
    return true;
}