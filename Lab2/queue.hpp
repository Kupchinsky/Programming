#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include <iostream>
#include <ostream>

enum class QueueExceptionCause
{
    HeadNotFound
};

class QueueException: public std::exception
{
    QueueExceptionCause cause;

public:
    QueueException(QueueExceptionCause cause)
    {
        this->cause = cause;
    }

    /**
     * Причина появления исключения
     * @return {const char*} Строка
     */
    virtual const char* what() const throw()
    {
        switch (this->cause)
        {
            case QueueExceptionCause::HeadNotFound:
                return "Head not found!";
            default:
                return "Unknown";
        }
    }
};

template <typename T>
class Queue
{
    struct QueueNode
    {
        T item;
        QueueNode *nextNode;
    };

    QueueNode *firstNode;
public:
    Queue();
    ~Queue();

    void add(T);
    T poll();
    T peek();

    unsigned int size();
};

#include "queue.tpp"

#endif // QUEUE_HPP
