#include "binarytree.hpp"
#include <cmath>

Node* BinaryTree::push(Node* & root, const wstring& newval)
{
    if (root == NULL)
    {
        root = new Node;

        root->item = newval;
        root->left = NULL;
        root->right = NULL;

        return root;
    }
    else
    {
        if (root->left == NULL)
            return push(root->left, newval);
        else if(root->right == NULL)
            return push(root->right, newval);
    }

    return NULL;
}

void BinaryTree::pushRoot(const wstring& newval)
{
    this->root = new Node;

    this->root->item = newval;
    this->root->left = NULL;
    this->root->right = NULL;
}

void BinaryTree::clear(Node *root)
{
    if (root == NULL)
        return;

    if (root->left != NULL)
        clear(root->left);

    if (root->right != NULL)
        clear(root->right);

    if (root == this->root)
        this->root = NULL;

    delete root;
}

unsigned int BinaryTree::findLeafes(Node *root)
{
    if (root == NULL)
        return 0;
    else if (root->left == NULL && root->right == NULL)
        return 1;

    unsigned int count = 0;

    if (root->left != NULL)
        count += findLeafes(root->left);

    if (root->right != NULL)
        count += findLeafes(root->right);

    return count;
}

void BinaryTree::print(Node *p, int spaces)
{
    if (p != NULL)
    {
        if (p->right != NULL)
            print(p->right, spaces + 4);

        if (spaces != 0)
            cout << setw(spaces) << " ";

        if (p->right != NULL)
            cout << " /" << endl << setw(spaces) << " ";

        wcout << p->item << endl << " ";

        if (p->left != NULL)
        {
            cout << setw(spaces + 3) << " \\" << endl;
            print(p->left, spaces + 4);
        }
    }
}

unsigned int BinaryTree::size(Node *root)
{
    if (root == NULL)
        return 0;

    unsigned int count = 1;

    if (root->left != NULL)
        count += size(root->left);

    if (root->right != NULL)
        count += size(root->right);

    return count;
}

unsigned int BinaryTree::height(Node *root)
{
    if (root == NULL)
        return 0;

    int h1 = 0, h2 = 0;

    if (root->left != NULL)
        h1 = height(root->left);

    if (root->right != NULL)
        h2 = height(root->right);

    return std::max(h1, h2) + 1;
}

BinaryTree::BinaryTree(): root(NULL)
{
}

BinaryTree::~BinaryTree()
{
    clear();
}

void BinaryTree::clear()
{
    clear(this->root);
}

void BinaryTree::print()
{
    print(root, 0);
    cout << endl;
}

unsigned int BinaryTree::size()
{
    return size(root);
}

unsigned int BinaryTree::height()
{
    return height(root);
}
