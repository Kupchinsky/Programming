#include <iostream>
#include <iomanip>
#include "binarytree.hpp"

using namespace std;

#define out(x) wcout << x << endl

int main()
{
    setlocale(LC_ALL, "Russian");

    BinaryTree *mytree = new BinaryTree();

    mytree->push(10);
    mytree->push(11);
    mytree->push(12);
    mytree->push(25);
    mytree->push(5);
    mytree->push(3);
    mytree->push(2);
    mytree->push(4);
    mytree->push(6);
    mytree->push(9);
    mytree->push(8);
    mytree->print();

    out(L"Размер дерева: " << mytree->size());
    out(L"Сумма: " << mytree->summ());
    out(L"Среднее: " << mytree->average());
    out(L"Макс. значение: " << mytree->max());
    out(L"Высота: " << mytree->height());

    delete mytree;
    return 0;
}

