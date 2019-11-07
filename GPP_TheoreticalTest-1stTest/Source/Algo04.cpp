/*  C++ Algorithms 4
    
    Given the struct BSTNode which represents a node in a binary search tree, write a function BSTMerge() that will merge the contents of two search trees into one.
    The function does not need to preserve the contents of the input trees.
*/

#include <iostream>
#include <random>

struct BSTNode
{
    BSTNode(int data): m_data(data), m_left(nullptr), m_right(nullptr) {}

    int m_data;
    BSTNode *m_left, *m_right;
};

BSTNode *BSTMerge(BSTNode *tree1, BSTNode *tree2)
{
    // This doesn't seem to really work
    return tree1;
}

void BSTInsert(BSTNode *&root, int data)
{
    BSTNode **ptr = &root;
    while (*ptr)
    {
        if (data < (*ptr)->m_data)
            ptr = &(*ptr)->m_left;
        else
            ptr = &(*ptr)->m_right;
    }
    *ptr = new BSTNode(data);
}

BSTNode *BSTGenerate(unsigned n)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> randData(0, 10000);

    BSTNode *root = nullptr;
    while (n--)
        BSTInsert(root, randData(rng));
    return root;
}

void BSTPrint(BSTNode *node)
{
    if (!node)
        return;
    BSTPrint(node->m_left);
    std::cout << node->m_data << std::endl;
    BSTPrint(node->m_right);
}

void main(int argc, char* argv[])
{
    BSTNode *tree1 = BSTGenerate(20);
    BSTNode *tree2 = BSTGenerate(15);

    BSTNode *merged = BSTMerge(tree1, tree2);

    BSTPrint(merged);
}