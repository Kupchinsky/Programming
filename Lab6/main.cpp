#include <iostream>
#include <iomanip>
#include <fstream>
#include "contacttree.hpp"
#include <windows.h>

using namespace std;

#define out(x) wcout << x << endl
#define outn(x) wcout << x
#define W(x) const_cast<wchar_t*>(x)
#define strbool(x) (x ? L"Да" : L"Нет")
#define LISTFILE "list.txt"

// Boost
bool isequal(const wstring& first, const wstring& second)
{
    if (first.size() != second.size())
        return false;

    for (wstring::size_type i = 0; i < first.size(); i++)
    {
        if (first[i] != second[i] && first[i] != (second[i] ^ 32))
            return false;
    }

    return true;
}

void getResponseLine(wstring& response)
{
    SetConsoleCP(1251);
    getline(wcin, response);
    SetConsoleCP(866);
}

void writeTree(ContactTree* tree)
{
    wofstream of;
    of.open(LISTFILE, ios::out);
    tree->writeToStream(of);
    of.close();
}

void readTree(ContactTree* tree)
{
    wifstream ifs;
    ifs.open(LISTFILE, ios::in);

    if (ifs.is_open())
    {
        tree->readFromStream(ifs);
        ifs.close();
    }
    else
    {
        ContactData data;

        data.Address = W(L"ул. Пети");
        data.FirstName = W(L"Петя");
        data.LastName = W(L"Иванов");
        data.Number = W(L"+712345679");

        tree->push(data);

        data.Address = W(L"ул. Петрова");
        data.FirstName = W(L"Петя");
        data.LastName = W(L"Петров");
        data.Number = W(L"+712345679");

        tree->push(data);
    }
}

int main()
{
    ContactTree *mytree = new ContactTree();

    readTree(mytree);

    mytree->print();
    wcout << "========================" << endl;

    ContactData *cc = NULL;
    mytree->find(W(L"петро"), cc);

    wcout << L"NULL: " << strbool(cc == NULL) << endl;

    if (cc != NULL)
    {
        wcout << L"Нашли: - " << cc->LastName << " ("
              << cc->FirstName << ", "
              << cc->Number << ", "
              << cc->Address << ")"
              << endl << endl;

        wcout << L"Удалено: " << strbool(mytree->remove(cc)) << endl << endl;
    }

    mytree->print();

    //writeTree(mytree);

    delete mytree;

    return 0;
}

