#include "binarytree.hpp"

void BinaryTree::push(Node* &root, int newval)
{
    if (root == NULL)
    {
        root = new Node;

        root->height = 1;
        root->item = newval;
        root->left = NULL;
        root->right = NULL;
    }
    else
    {
        if (newval < root->item)
            push(root->left, newval);
        else if(newval > root->item)
            push(root->right, newval);

        root->height++;
    }
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

        cout << p->item << endl << " ";

        if (p->left != NULL)
        {
            cout << setw(spaces + 3) << " \\" << endl;
            print(p->left, spaces + 4);
        }
    }
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

int BinaryTree::summ(Node *root)
{
    if (root == NULL)
        return 0;

    int result = root->item;

    if (root->left != NULL)
        result += summ(root->left);

    if (root->right != NULL)
        result += summ(root->right);

    return result;
}

int BinaryTree::max(Node *root)
{
    return root->right != NULL ? max(root->right) : root->item;
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
    return root != NULL ? root->height : 0;
}

BinaryTree::BinaryTree(): root(NULL)
{
}

BinaryTree::~BinaryTree()
{
    clear(this->root);
}

void BinaryTree::clear()
{
    clear(this->root);
}

void BinaryTree::push(int newval)
{
    push(root, newval);
}

void BinaryTree::print()
{
    print(root, 0);
    cout << endl;
}

int BinaryTree::max()
{
    return max(root);
}

int BinaryTree::summ()
{
    return summ(root);
}

float BinaryTree::average()
{
    return summ() / (float)size();
}

unsigned int BinaryTree::size()
{
    return size(root);
}

unsigned int BinaryTree::height()
{
    return height(root);
}