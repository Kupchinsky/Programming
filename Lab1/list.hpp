#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <iostream>
#include <ostream>

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

template <typename T>
class List
{
    struct ListNode
    {
        T item;
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

    // 2.1. Напишите функцию, вставляющую узел в начало связанного списка и функцию, удаляющую этот узел.
    void pushFirst(T);
    void deleteFirst();
    //

    void deleteNode(ListNode*);

    // 2.2. Повторите предыдущее задание, на этот раз вставляя и удаляя не первый, а последний элемент списка.
    // 2.3. Повторите предыдущее задание, считая что существуют указатели на голову и хвост списка.
    void pushLast(T);
    void deleteLast();
    //

    T get(unsigned int index);
    T first();
    T last();

    // 3. Напишите функцию для подсчета количества узлов в связанном списке.
    // 3.1. Итеративно.
    unsigned int calculateSize();
    //

    // 3.2. Рекурсивно.
    unsigned int calculateSizeRecursive();
    //

    // 4. Напишите функцию для удаления узла, содержащего наибольшее целое число, из связанного списка целых чисел.
    void deleteMostGreaterNode();
    //

    // Слияние упорядоченных списков
    List* mergeLists(List*);
    //

    void print(std::ostream*);
};

#include "list.tpp"

#endif // LIST_HPP
