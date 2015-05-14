#ifndef CTASKMENU_H
#define CTASKMENU_H

#include <vector>

using namespace std;

typedef void (*TaskMenuCallback)();

class CTaskMenu
{
    struct TaskMenuData
    {
        wstring description;
        TaskMenuCallback callback;
    };

    vector<TaskMenuData> data;
    string color = "F1";
public:
    CTaskMenu* addTask(wstring, TaskMenuCallback);
    CTaskMenu* setColor(string);
    CTaskMenu* loop();
};
#endif
