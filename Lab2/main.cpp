#include "queue.hpp"
#include <iostream>
#include <fstream>

using namespace std;

#define out(x) wcout << x << endl

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
            waitTime = 0,      // Время ожидания конкретного посетителя
            allWaitTime = 0,   // Общее время ожидания
            waitVisitors = 0, // Количество посетителей, которые ожидали очередь
            visitorsCount = 0; // Количество посетителей

    while (visitors->size() > 0 || arrivedVisitors->size() > 0)
    {
        currentTime++;

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
            Visitor current = arrivedVisitors->peek();
            bool minusOne = true;

            if (nextTime + current.duration == currentTime)
            {
                nextTime += current.duration;
                arrivedVisitors->poll(); // Удаляем посетителя

                out(L"Обработка отбытия в момент: " << currentTime);
                out(L"Кто-то ещё ждал: " << waitTime);

                if (waitTime > 0)
                {
                    out(L"Ждало: " << arrivedVisitors->size());
                    waitVisitors += arrivedVisitors->size();
                    allWaitTime += waitTime;
                }

                waitTime = 0;
                minusOne = false;
            }

            waitTime += arrivedVisitors->size() - (minusOne ? 1 : 0);
        }
        else
        {
            if (nextTime > 0) // Посетители отсутствуют, но время следующего не сброшено
                nextTime = 0; // Время отбытия обнуляем
        }
    }

    out(L"Конец моделирования" << endl
        << L"   Общее количество посетителей: " << visitorsCount << endl
        << L"   Среднее время ожидания в очереди: " << allWaitTime - 1 << " " << waitVisitors);

    return 0;
}

