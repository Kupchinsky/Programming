#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>
#include <iomanip>

using namespace std;

struct Node
{
    wstring item;
    Node *left;
    Node *right;
};

class BinaryTree
{
    Node *root;

    void print(Node *, int);
    void clear(Node *);
    unsigned int findLeafes(Node*);
    unsigned int size(Node *);
    unsigned int height(Node *);

public:
    BinaryTree();
    ~BinaryTree();

    void clear();
    Node* push(Node* &, const wstring&);
    void pushRoot(const wstring&);
    void print();
    unsigned int size();
    unsigned int height();
    Node* getRoot() const
    {
        return this->root;
    }
};
#endif // BINARYTREE_HPP
