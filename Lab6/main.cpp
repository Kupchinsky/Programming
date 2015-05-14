#include <iostream>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include "contacttree.hpp"
#include "TaskMenu.h"

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

    for(wstring::size_type i = 0; i < first.size(); i++)
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

bool getResponseBool()
{
    wstring response;
    getResponseLine(response);

    return isequal(response, L"да");
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
        // Default
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

ContactTree *mytree = new ContactTree();

void cdAdd()
{
    ContactData data;

    wcin.ignore();

    outn(L"Имя: ");
    getResponseLine(data.FirstName);

    outn(L"Фамилия: ");
    getResponseLine(data.LastName);

    outn(L"Номер: ");
    getResponseLine(data.Number);

    outn(L"Адрес: ");
    getResponseLine(data.Address);

    mytree->push(data);

    writeTree(mytree);

    out(L"Контакт добавлен.");
}

ContactData* findData()
{
    wcin.ignore();

    wstring lastName;
    outn(L"Введите фамилию для поиска: ");
    getResponseLine(lastName);

    if (lastName.length() == 0)
        return NULL;

    ContactData *data;
    mytree->find(lastName, data);

    if (data != NULL)
        out(L"Нашли: - " << data->LastName << L" (Имя: "
              << data->FirstName << L", Номер: "
              << data->Number << L", Адрес: "
              << data->Address << ")");

    return data;
}

ContactData *currentEdit = NULL;

void cdEditSuccess()
{
    writeTree(mytree);
    out(L"Контакт изменён.");
}

void cdEditChild1()
{
    outn(L"Новое имя: ");
    wcin.ignore();
    wstring newValue;
    getResponseLine(newValue);

    if (newValue.length() != 0)
    {
        currentEdit->FirstName = newValue;
        cdEditSuccess();
    }
}

void cdEditChild2()
{
    outn(L"Новый номер: ");
    wcin.ignore();
    wstring newValue;
    getResponseLine(newValue);

    if (newValue.length() != 0)
    {
        currentEdit->Number = newValue;
        cdEditSuccess();
    }
}

void cdEditChild3()
{
    outn(L"Новый адрес: ");
    wcin.ignore();
    wstring newValue;
    getResponseLine(newValue);

    if (newValue.length() != 0)
    {
        currentEdit->Address = newValue;
        cdEditSuccess();
    }
}

void cdEdit()
{
    currentEdit = findData();

    if (currentEdit == NULL)
    {
        out(L"Контакт не найден!");
        return;
    }

    delete (new CTaskMenu())
            ->setColor("FF")
            ->addTask(W(L"Изменить имя"), cdEditChild1)
            ->addTask(W(L"Изменить номер"), cdEditChild2)
            ->addTask(W(L"Изменить адрес"), cdEditChild3)
            ->loop();
}

void cdRemove()
{
    ContactData *data = findData();

    if (data == NULL)
    {
        out(L"Контакт не найден!");
        return;
    }

    outn(L"Подтверждаете удаление? ");

    bool rem = getResponseBool() && mytree->remove(data);
    out(L"Удаление завершено: " << strbool(rem));

    if (rem)
        writeTree(mytree);
}

void cdFind()
{
    ContactData *data = findData();

    if (data == NULL)
    {
        out(L"Контакт не найден!");
        return;
    }
}

void cdPrint()
{
    mytree->print();
}

int main()
{
    setlocale(LC_ALL, "Russian");

    readTree(mytree);

    delete (new CTaskMenu())
            ->setColor("FF")
            ->addTask(W(L"Добавить контакт"), cdAdd)
            ->addTask(W(L"Изменить контакт"), cdEdit)
            ->addTask(W(L"Удалить контакт"), cdRemove)
            ->addTask(W(L"Найти контакт"), cdFind)
            ->addTask(W(L"Вывести все контакты"), cdPrint)
            ->loop();

    out(L"Выход...");

    delete mytree;
    return 0;
}

