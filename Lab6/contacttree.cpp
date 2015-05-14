#include "contacttree.hpp"
#include <cmath>

void ContactTree::push(Node* & root, const ContactData& newval)
{
    if (root == NULL)
    {
        root = new Node;

        root->item = newval;
        root->left = NULL;
        root->right = NULL;
    }
    else
    {
        if (newval.LastName[0] < root->item.LastName[0])
            push(root->left, newval);
        else if(newval.LastName[0] > root->item.LastName[0])
            push(root->right, newval);
    }
}

void ContactTree::clear(Node *root)
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

void ContactTree::print(Node *p, int spaces)
{
    if (p != NULL)
    {
        if (p->right != NULL)
            print(p->right, spaces + 4);

        if (spaces != 0)
            cout << setw(spaces) << " ";

        if (p->right != NULL)
            cout << " /" << endl << setw(spaces) << " ";

        wcout << " - " << p->item.LastName << " ("
              << p->item.FirstName << ", "
              << p->item.Number << ", "
              << p->item.Address << ")"
              << endl << " ";

        if (p->left != NULL)
        {
            cout << setw(spaces + 3) << " \\" << endl;
            print(p->left, spaces + 4);
        }
    }
}

ContactTree::ContactTree(): root(NULL)
{
}

ContactTree::~ContactTree()
{
    clear();
}

void ContactTree::clear()
{
    clear(this->root);
}

void ContactTree::push(const ContactData& newval)
{
    push(root, newval);
}

void ContactTree::print()
{
    print(root, 0);
    cout << endl;
}

void ContactTree::writeToStream(Node *root, wostream& out)
{
    if (root == NULL)
        return;

    out << root->item.FirstName << endl
        << root->item.LastName << endl
        << root->item.Address << endl
        << root->item.Number << endl
        << endl;

    if (root->right != NULL)
        writeToStream(root->right, out);

    if (root->left != NULL)
        writeToStream(root->left, out);
}

void ContactTree::writeToStream(wostream& out)
{
    writeToStream(root, out);
}

void ContactTree::readFromStream(wistream& in)
{
    while (!in.eof())
    {
        wstring Split;
        ContactData cd;

        getline(in, cd.FirstName);

        if (cd.FirstName.length() == 0) // Последняя пустая строка
            break;

        getline(in, cd.LastName);
        getline(in, cd.Address);
        getline(in, cd.Number);
        getline(in, Split);

        push(cd);
    }
}

Node* ContactTree::find(Node *root, const wstring& lastName)
{
    if (root == NULL)
        return NULL;

    if (ContactTree::str_startsWith(root->item.LastName, lastName))
        return root;
    else
    {
        Node *child = find(root->left, lastName);

        if (child == NULL)
            child = find(root->right, lastName);

        return child;
    }
}

Node* ContactTree::findByRef(Node *root, const ContactData*& item, Node*& parent)
{
    if (root == NULL)
        return NULL;

    if (&root->item == item)
        return root;
    else
    {
        parent = root;

        Node *child = findByRef(root->left, item, parent);

        if (child == NULL)
            child = findByRef(root->right, item, parent);

        return child;
    }
}

void ContactTree::find(const wstring& lastName, ContactData* &item)
{
    Node *found = find(root, lastName);
    item = (found != NULL ? &found->item : NULL);
}

bool ContactTree::str_startsWith(const wstring& str, const wstring& check)
{
    for (wstring::size_type i = 0; i < check.size(); i++)
    {
        if (str[i] != check[i] && str[i] != (check[i] ^ 32))
            return false;
    }

    return true;
}

bool ContactTree::remove(const ContactData* item)
{
    Node *parentRef = NULL, *found = findByRef(root, item, parentRef);

    if (found == NULL)
        return false;

    Node *savedRoot = this->root;

    this->root = NULL;

    vector<Node*> skipNodes;
    skipNodes.push_back(found);

    pushAll(savedRoot, skipNodes);
    clear(savedRoot);

    return true;
}

void ContactTree::pushAll(Node* root, vector<Node*>& skip)
{
    if (root == NULL)
        return;

    bool found = false;

    for (unsigned int i = 0; i < skip.size(); i++)
    {
        if (skip[i] == root)
        {
            found = true;
            break;
        }
    }

    if (!found)
        push(root->item);

    if (root->left != NULL)
        pushAll(root->left, skip);

    if (root->right != NULL)
        pushAll(root->right, skip);
}
