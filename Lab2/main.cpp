#include "queue.hpp"
#include <iostream>
#include <fstream>

using namespace std;

#define _DEBUG 0
#define out(x) wcout << x << endl

#if _DEBUG > 0
#define trace(x) wcout << "     " << x << endl
#else
#define trace(x)
#endif

struct Visitor
{
    int timeArrive, duration;
};

int main()
{
    setlocale(LC_ALL, "Russian");

    Queue<Visitor> *visitors = new Queue<Visitor>(), *arrivedVisitors = new Queue<Visitor>();

    ifstream ifs("..\\input.txt", ios::in);

    while (!ifs.eof())
    {
        Visitor newVisitor;

        ifs >> newVisitor.timeArrive >> newVisitor.duration;
        visitors->add(newVisitor);
    }

    // Задание
    out(L"Начало моделирования...");
    int
            currentTime = 0,   // Текущее время
            nextTime = 0,      // Следующее время отбытия посетителя
            waitTime = 0,      // Общее время ожидания
            visitorsCount = 0; // Количество посетителей

    while (visitors->size() > 0 || arrivedVisitors->size() > 0)
    {
        currentTime++;

        trace(L"Текущее время: " << currentTime);

        // Прибытие
        if (visitors->size() > 0 && visitors->peek().timeArrive == currentTime) // Время прибытия равно текущему времени
        {
            Visitor current = visitors->poll();

            arrivedVisitors->add(current); // Добавляем в очередь прибывших
            visitorsCount++; // Количество посетителей стало больше

            if (nextTime == 0)
                nextTime = current.timeArrive;

            out(L"Обработка прибытия в момент: " << currentTime);
        }

        // Отбытие
        if (arrivedVisitors->size() > 0)
        {
            trace(L"Очередь не пустая, проверяем");
            Visitor current = arrivedVisitors->peek();

            if (nextTime + current.duration == currentTime)
            {
                nextTime += current.duration;
                trace("nextTime = " << nextTime);

                arrivedVisitors->poll(); // Удаляем посетителя

                out(L"Обработка отбытия в момент: " << currentTime);
            }
            else
                trace(L"Посетитель отбудет в момент времени " << nextTime);

            //if (arrivedVisitors->size() > 1)
            //    waitTime++;
        }
        else
        {
            if (nextTime > 0) // Посетители отсутствуют, но время следующего не сброшено
            {
                nextTime = 0; // Время отбытия обнуляем
                trace("nextTime = 0");
            }
        }
    }

    out(L"Конец моделирования" << endl
        << L"   Общее количество посетителей: " << visitorsCount << endl
        << L"   Среднее время ожидания в очереди: " << waitTime);

    return 0;
}

