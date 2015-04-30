#include <iostream>
#include <iomanip>
#include "binarytree.hpp"

using namespace std;

#define out(x) wcout << x << endl
#define strbool(x) (x ? L"Да" : L"Нет")

int main()
{
    setlocale(LC_ALL, "Russian");

    BinaryTree *mytree = new BinaryTree();

    // Заполненное
    mytree->push(10);
    mytree->push(13);
    mytree->push(12);
    mytree->push(14);
    mytree->push(8);
    mytree->push(7);
    mytree->push(9);

   /* mytree->push(10);
    mytree->push(11);
    mytree->push(12);
    mytree->push(25);
    mytree->push(5);
    mytree->push(3);
    mytree->push(2);
    mytree->push(4);
    mytree->push(6);
    mytree->push(9);
    mytree->push(8);*/
    mytree->print();

    out(L"Размер дерева: " << mytree->size());
    out(L"Сумма: " << mytree->summ());
    out(L"Среднее значение: " << mytree->average());
    out(L"Макс. значение: " << mytree->max());
    out(L"Высота: " << mytree->height());

    int parent = 3, child = 2;
    out(L"Является ли предком числа " << child << L" число " << parent << ": " << strbool(mytree->isChild(parent, child)));

    int find = 4;
    out(L"Есть ли в дереве число " << find << ": " << strbool(mytree->find(find)));

    out(L"Заполнено ли дерево: " << strbool(mytree->isFilled()));

    delete mytree;
    return 0;
}

