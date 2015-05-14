#include <vector>
#include <iostream>
#include <stdlib.h>
#include <TaskMenu.h>
#include <windows.h>

#define W(x) const_cast<wchar_t*>(x)

using namespace std;

CTaskMenu* CTaskMenu::addTask(wstring desc, TaskMenuCallback cb)
{
    TaskMenuData dt;

    dt.description = desc;
    dt.callback = cb;

    data.push_back(dt);

    return this;
}

CTaskMenu* CTaskMenu::setColor(string color)
{
    this->color = color;
    return this;
}

CTaskMenu* CTaskMenu::loop()
{
    setlocale(LC_ALL, "Russian");

    string color_cmd = "color ";
    color_cmd += this->color.c_str();

    system(color_cmd.c_str());

    while (true)
    {
        unsigned int cmd;

        wcout << L"============ Меню ============" << endl;

        for (unsigned int i = 0; i < data.size(); i++)
            wcout << i + 1 << " - " << data[i].description << endl;

        wcout << L"0 - Выход" << endl << endl << L"Введите команду: ";

        wcin >> cmd;

        if (cmd == 0)
            break;

        if (cmd <= data.size())
        {
            wcout << L"Выполнение:" << endl;
            data[cmd - 1].callback();
        }

        wcout << endl;
    }

    return this;
}

