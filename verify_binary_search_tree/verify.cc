#include <iostream>
#include <limits>

using namespace std;

struct Node
{
    int val;

    Node* left;
    Node* right;
};

bool IsBinarySearchTree(Node* node, int left_limit, int right_limit)
{
    if (node == NULL)
    {
        return true;
    }

    if (node->val <= left_limit || node->val >= right_limit)
    {
        return false;
    }

    return IsBinarySearchTree(node->left, left_limit, node->val) && IsBinarySearchTree(node->right, node->val, right_limit);
}

bool IsBinarySearchTree(Node* head)
{
    return IsBinarySearchTree(head, numeric_limits<int>::min(), numeric_limits<int>::max());
}

int main()
{
    return 0;
}

