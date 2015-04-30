#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP
#include <iostream>
#include <iomanip>

using namespace std;

struct Node
{
    int item, height;
    Node *left;
    Node *right;
};

class BinaryTree
{
    Node *root;

    void push(Node* &, int);
    void print(Node *, int);
    void clear(Node *);
    int summ(Node *);
    int max(Node *);
    unsigned int size(Node *);
    unsigned int height(Node *);

public:
    BinaryTree();
    ~BinaryTree();

    void clear();
    void push(int);
    void print();
    int max();
    int summ();
    float average();
    unsigned int size();
    unsigned int height();
};
#endif // BINARYTREE_HPP
