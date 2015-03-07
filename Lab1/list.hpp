#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <iostream>
#include <ostream>

#define _LIST_TYPE int

enum class ListExceptionCause
{
    ElementNotFound,
    ElementsNotFound
};

class ListException: public std::exception
{
    ListExceptionCause cause;

public:
    ListException(ListExceptionCause cause)
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
            case ListExceptionCause::ElementNotFound:
                return "Element not found!";
            default:
                return "Unknown";
        }
    }
};

class List
{
    struct ListNode
    {
        _LIST_TYPE item;
        ListNode *nextNode;
    };

    ListNode *firstNode;
    bool notClear;

    List(ListNode*);
    ListNode *getFirstNode();
    void noClear();
    unsigned int _calculateSizeRecursive(ListNode);
    ListNode* getNode(unsigned int index);
public:
    List();
    ~List();

    void swapNodes(unsigned int index1, unsigned int index2);
    void pushFirst(_LIST_TYPE);
    void deleteFirst();
    void deleteNode(ListNode*);
    void pushLast(_LIST_TYPE);
    void deleteLast();

    _LIST_TYPE get(unsigned int index);
    _LIST_TYPE first();
    _LIST_TYPE last();

    unsigned int calculateSize();
    unsigned int calculateSizeRecursive();

    void deleteMostGreaterNode();
    List* mergeLists(List*);
    void print(std::ostream*);
};

#endif // LIST_HPP
