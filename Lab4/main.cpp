#include <iostream>
#include <iomanip>
#include <algorithm>
#include "binarytree.hpp"
#include <windows.h>

using namespace std;

#define out(x) wcout << x << endl
#define outn(x) wcout << x
#define W(x) const_cast<wchar_t*>(x)
#define strbool(x) (x ? L"Да" : L"Нет")

// Boost
bool isequal(const wstring& first, const wstring& second)
{
    if (first.size() != second.size())
        return false;

    for(wstring::size_type i = 0; i < first.size(); i++)
    {
        if (first[i] != second[i] && first[i] != (second[i] ^ 32))
            return false;
    }

    return true;
}

bool isLeaf(Node* node)
{
    return node->left == NULL && node->right == NULL;
}

void getResponseLine(wstring& response)
{
    SetConsoleCP(1251);
    getline(wcin, response);
    SetConsoleCP(866);
}

bool getResponseBool()
{
    wstring response;
    getResponseLine(response);

    return isequal(response, L"да");
}

int main()
{
    setlocale(LC_ALL, "Russian");

    BinaryTree *mytree = new BinaryTree();

    mytree->pushRoot(W(L"У него есть ноги?"));

    Node *root = mytree->getRoot();
    mytree->push(root, W(L"Кошка")); // Да
    mytree->push(root, W(L"Змея"));  // Нет

    bool working = true;

    while (working)
    {
        out(L"Задумайте животное и я его отгадаю.");

        Node *nextNode = root;

        while (true)
        {
            // Формируем вопрос
            if (isLeaf(nextNode))
            {
                outn(L"Это " << nextNode->item << "? ");

                if (getResponseBool())
                    outn(L"Я победила! Играем дальше? ");
                else
                {
                    outn(L"Я сдаюсь! Что это? ");

                    // Получаем ответ (название животного)
                    wstring newCaption;
                    getResponseLine(newCaption);

                    // Получаем новый вопрос
                    outn(L"Пожалуйста, наберите на клавиатуре вопрос с положительным ответом для " << newCaption << L" и отрицательным для " << nextNode->item << ": ");

                    wstring newQuestion;
                    getResponseLine(newQuestion);

                    // Сохраняем название
                    wstring savedCaption = nextNode->item;

                    nextNode->item = newQuestion;

                    mytree->push(nextNode, newCaption);
                    mytree->push(nextNode, savedCaption);

                    outn(L"Играем дальше? ");
                }

                working = getResponseBool();
                break;
            }
            else
            {
                outn(nextNode->item << " ");
                nextNode = getResponseBool() ? nextNode->left : nextNode->right;
            }
        }

        outn(endl);
    }

    out(L"До свидания.");

    delete mytree;
    return 0;
}

