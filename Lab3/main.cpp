#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define out(x) wcout << x << endl

struct Node
{
    int item, height;
    Node *left;
    Node *right;
};

class BinaryTree
{
    Node *root;

    void Push(Node* &root, int newval)
    {
        if (root == NULL)
        {
            root = new Node;
            root->height = 1;
            root->item = newval;
            root->left = NULL;
            root->right = NULL;

            //out("New node: " << newval);
        }
        else
        {
            if (newval < root->item)
            {
                //out("Root: " << root->item << "; Push left: " << newval);
                Push(root->left, newval);
            }
            else if(newval > root->item)
            {
                //out("Root: " << root->item << "; Push right: " << newval);
                Push(root->right, newval);
            }

            root->height++;
        }
    }

    void Print(Node *p, int spaces)
    {
        if (p != NULL)
        {
            if (p->right != NULL)
                Print(p->right, spaces + 4);

            if (spaces != 0)
                cout << setw(spaces) << " ";

            if (p->right != NULL)
                cout << " /" << endl << setw(spaces) << " ";

            cout << p->item << endl << " ";

            if (p->left != NULL)
            {
                cout << setw(spaces + 3) << " \\" << endl;
                Print(p->left, spaces + 4);
            }
        }
    }

    unsigned int Size(Node *root)
    {
        if (root == NULL)
            return 0;

        unsigned int count = 1;

        if (root->left != NULL)
            count += Size(root->left);

        if (root->right != NULL)
            count += Size(root->right);

        return count;
    }

    void ClearTree(Node *root)
    {
        if (root == NULL)
            return;

        if (root->left != NULL)
            ClearTree(root->left);

        if (root->right != NULL)
            ClearTree(root->right);

        if (root == this->root)
            this->root = NULL;

        delete root;
    }

    int GetSumm(Node *root)
    {
        if (root == NULL)
            return 0;

        int summ = root->item;

        if (root->left != NULL)
            summ += GetSumm(root->left);

        if (root->right != NULL)
            summ += GetSumm(root->right);

        return summ;
    }

    int GetMax(Node *root)
    {
        return root->right != NULL ? GetMax(root->right) : root->item;
    }

    unsigned int GetHeight(Node *root)
    {
        return root != NULL ? root->height : 0;
    }

public:
    BinaryTree(): root(NULL)
    {
    }

    ~BinaryTree()
    {
        ClearTree(this->root);
    }

    void ClearTree()
    {
        ClearTree(this->root);
    }

    void Push(int x)
    {
        Push(root, x);
    }

    void Print()
    {
        Print(root, 0);
        cout << endl;
    }

    unsigned int Size()
    {
        return Size(root);
    }

    int GetMax()
    {
        return GetMax(root);
    }

    int GetSumm()
    {
        return GetSumm(root);
    }

    float GetAverage()
    {
        return GetSumm() / (float)Size();
    }

    unsigned int GetHeight()
    {
        return GetHeight(root);
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    BinaryTree TREE;

    TREE.Push(10);
    TREE.Push(11);
    TREE.Push(12);
    TREE.Push(25);
    TREE.Push(5);
    TREE.Push(3);
    TREE.Push(2);
    TREE.Push(4);
    TREE.Push(6);
    TREE.Push(9);
    TREE.Push(8);
    TREE.Print();

    cout << "Size: " << TREE.Size() << endl;
    cout << "Summ: " << TREE.GetSumm() << endl;
    cout << "Average: " << TREE.GetAverage() << endl;
    cout << "Max: " << TREE.GetMax() << endl;
    cout << "Height: " << TREE.GetHeight() << endl;

    TREE.ClearTree();

    return 0;
}

