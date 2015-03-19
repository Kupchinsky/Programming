#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include <iostream>
#include <ostream>

#define _QUEUE_TYPE int


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

class Queue
{
    struct QueueNode
    {
        _QUEUE_TYPE item;
        QueueNode *nextNode;
    };

    QueueNode *firstNode;
public:
    Queue();
    ~Queue();

    void add(_QUEUE_TYPE);
    _QUEUE_TYPE poll();
    _QUEUE_TYPE peek();

    unsigned int size();
};

#endif // QUEUE_HPP
