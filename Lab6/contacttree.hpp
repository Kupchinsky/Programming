#ifndef CONTACTTREE_HPP
#define CONTACTTREE_HPP

#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct ContactData
{
    wstring FirstName, LastName, Address, Number;
};

struct Node
{
    ContactData item;
    Node *left, *right;
};

class ContactTree
{
    Node *root;

    void print(Node *, int);
    void clear(Node *);
    void push(Node* &, const ContactData&);
    void writeToStream(Node *, wostream &);
    void pushAll(Node*, vector<Node*>&);
    Node* find(Node *, const wstring&);
    Node* findByRef(Node *, const ContactData*&, Node*&);

    static bool str_startsWith(const wstring&, const wstring&);

public:
    ContactTree();
    ~ContactTree();

    void clear();
    void push(const ContactData&);
    void print();
    void find(const wstring&, ContactData* &);
    bool remove(const ContactData*);

    void writeToStream(wostream &);
    void readFromStream(wistream &);
};
#endif // CONTACTTREE_HPP
