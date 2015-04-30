#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>
#include <iomanip>

using namespace std;

struct Node
{
    int item;
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
    Node* find(Node *, int);
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
    bool isChild(int, int);
    bool find(int);
    unsigned int size();
    unsigned int height();
};
#endif // BINARYTREE_HPP
