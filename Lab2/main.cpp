#include "queue.hpp"
#include <iostream>
#include <fstream>

using namespace std;

#define out(x) wcout << x << endl

struct User
{
    int timeArrive, timeServed;
};

#include "..\Lab1\list.hpp"

int main()
{
    setlocale(LC_ALL, "Russian");

    // Testing queues
    Queue<int> *q1 = new Queue<int>();

    for (int i = 0; i < 5; i++)
        q1->add(i);

    for (int i = 0; i < 5; i++)
        out(i << ": " << q1->poll());
    //

    List<User> *users = new List<User>();

    ifstream ifs("..\\input.txt", ios::in);

    while (!ifs.eof())
    {
        User newUser;

        ifs >> newUser.timeArrive >> newUser.timeServed;
        users->pushLast(newUser);
    }

    return 0;
}

