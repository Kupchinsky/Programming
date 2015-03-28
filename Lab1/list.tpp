#include "list.hpp"

template <typename T>
List<T>::List(ListNode *_firstNode): firstNode(_firstNode), notClear(false)
{
}

template <typename T>
List<T>::List(): firstNode(NULL), notClear(false)
{
}

template <typename T>
List<T>::~List()
{
    if (this->firstNode == NULL || this->notClear)
        return;

    ListNode *currentNode = this->firstNode;

    do
    {
        ListNode *nextNode = currentNode->nextNode;

        delete currentNode;
        currentNode = nextNode;
    }
    while (currentNode != NULL);
}

template <typename T>
typename List<T>::ListNode* List<T>::getFirstNode()
{
    return this->firstNode;
}

template <typename T>
void List<T>::pushFirst(T newItem)
{
    ListNode *newNode = new ListNode;

    newNode->item = newItem;
    newNode->nextNode = this->firstNode;

    this->firstNode = newNode;
}

template <typename T>
void List<T>::deleteFirst()
{
    if (this->firstNode == NULL)
        throw ListException(ListExceptionCause::ElementsNotFound);

    ListNode *nextNode = this->firstNode->nextNode;

    delete this->firstNode;
    this->firstNode = nextNode;
}

template <typename T>
void List<T>::pushLast(T newItem)
{
    ListNode *lastNode = this->firstNode;

    if (lastNode != NULL)
    {
        for (; lastNode->nextNode != NULL; lastNode = lastNode->nextNode)
        {
        }
    }

    ListNode *newNode = new ListNode;

    newNode->item = newItem;
    newNode->nextNode = NULL;

    if (lastNode != NULL)
        lastNode->nextNode = newNode;
    else
        this->firstNode = newNode;
}

template <typename T>
void List<T>::deleteLast()
{
    ListNode *lastNode = this->firstNode, *prevNode = NULL;

    do
    {
        prevNode = lastNode;
        lastNode = lastNode->nextNode;
    }
    while (lastNode->nextNode != NULL);

    if (lastNode != NULL)
    {
        prevNode->nextNode = NULL;
        delete lastNode;
    }
}

template <typename T>
unsigned int List<T>::calculateSize()
{
    if (this->firstNode == NULL)
        return 0;

    ListNode *currentNode = this->firstNode;
    unsigned int returnSize = 0;

    do
    {
        returnSize++;
        currentNode = currentNode->nextNode;
    }
    while (currentNode != NULL);

    return returnSize;
}

template <typename T>
unsigned int List<T>::calculateSizeRecursive()
{
    return this->_calculateSizeRecursive(*this->firstNode);
}

template <typename T>
unsigned int List<T>::_calculateSizeRecursive(ListNode current)
{
    return (current.nextNode == NULL ? 1 : this->_calculateSizeRecursive(*current.nextNode) + 1);
}

template <typename T>
void List<T>::deleteMostGreaterNode()
{
    if (this->firstNode == NULL)
        throw ListException(ListExceptionCause::ElementsNotFound);

    ListNode
            *currentNode = this->firstNode, *prevNode = NULL,
            *prevSavedNode = NULL, *savedNode = this->firstNode;

    do
    {
        if (currentNode->item > savedNode->item)
        {
            prevSavedNode = prevNode;
            savedNode = currentNode;
        }

        prevNode = currentNode;
        currentNode = currentNode->nextNode;
    }
    while (currentNode != NULL);

    if (prevSavedNode != NULL)
        prevSavedNode->nextNode = savedNode->nextNode;
    else
        this->firstNode = savedNode->nextNode;

    delete savedNode;
}

template <typename T>
void List<T>::swapNodes(unsigned int index1, unsigned int index2)
{
    ListNode *firstNode = this->getNode(index1);
    ListNode *secondNode = this->getNode(index2);

    if (firstNode == this->firstNode || secondNode == this->firstNode)
    {
        bool b = (firstNode == this->firstNode);
        ListNode *savedNextNode = (b ? secondNode : firstNode)->nextNode;
        this->firstNode = (b ? secondNode : firstNode);

        ListNode *targetNode2 = (b ? firstNode : secondNode);

        (b ? secondNode : firstNode)->nextNode = targetNode2;
        targetNode2->nextNode = savedNextNode;
    }
    else
    {
        ListNode *firstNodePrev = this->getNode(index1 - 1);
        ListNode *secondNodePrev = this->getNode(index2 - 1);

        if (firstNode == secondNodePrev || secondNode == firstNodePrev)
        {
            bool b = (firstNode == secondNodePrev);
            ListNode *savedNextNode = (b ? secondNode : firstNode)->nextNode;
            ListNode *targetNode1 = (b ? firstNode : secondNode);
            ListNode *targetNode2 = (b ? secondNode : firstNode);

            (b ? firstNodePrev : secondNodePrev)->nextNode = targetNode2;
            targetNode2->nextNode = targetNode1;
            targetNode1->nextNode = savedNextNode;
        }
        else
        {
            ListNode *secondNode_nextNode = secondNode->nextNode;

            firstNodePrev->nextNode = secondNode;
            secondNode->nextNode = firstNode->nextNode;

            secondNodePrev->nextNode = firstNode;
            firstNode->nextNode = secondNode_nextNode;
        }
    }
}

template <typename T>
List<T>* List<T>::mergeLists(List *secondList)
{
    if (this->firstNode == NULL || secondList->getFirstNode() == NULL)
        throw ListException(ListExceptionCause::ElementsNotFound);

    this->noClear();
    secondList->noClear();

    unsigned int size = this->calculateSize() + secondList->calculateSize();

    List *createdList = new List();
    ListNode *lastNode = this->firstNode;

    /* Сливаем в один */
    do
    {
        lastNode = lastNode->nextNode;
    }
    while (lastNode->nextNode != NULL);

    lastNode->nextNode = secondList->getFirstNode();

    ListNode *lastMinNode = this->firstNode;

    for (unsigned int i = 0; i < size; i++)
    {
        lastNode = this->firstNode;

        for (; lastNode != NULL; lastNode = lastNode->nextNode)
        {
            if (lastMinNode->item > lastNode->item)
                lastMinNode = lastNode;
        }

        createdList->pushLast(lastMinNode->item);
        this->deleteNode(lastMinNode);
    }

    return createdList;
}

template <typename T>
void List<T>::deleteNode(ListNode* node)
{
    if (node == this->firstNode)
        this->firstNode = node->nextNode;
    else
    {
        ListNode *lastNode = this->firstNode;
        bool found = false;

        do
        {
            if (lastNode->nextNode == node)
            {
                found = true;
                break;
            }

            lastNode = lastNode->nextNode;
        }
        while (lastNode->nextNode != NULL);

        if (!found)
            throw ListException(ListExceptionCause::ElementNotFound);

        lastNode->nextNode = node->nextNode;
    }

    delete node;
}

template <typename T>
void List<T>::print(std::ostream *os)
{
    if (this->firstNode == NULL)
        throw ListException(ListExceptionCause::ElementsNotFound);

    ListNode *currentNode = this->firstNode;

    do
    {
        *os << "Element: " << currentNode->item << std::endl;
        currentNode = currentNode->nextNode;
    }
    while (currentNode != NULL);
}

template <typename T>
void List<T>::noClear()
{
    this->notClear = true;
}

template <typename T>
typename List<T>::ListNode* List<T>::getNode(unsigned int index)
{
    ListNode* lastNode = this->firstNode;
    unsigned int i = 0;

    for (; i != index && lastNode != NULL; i++, lastNode = lastNode->nextNode)
    {
    }

    if (index != i || lastNode == NULL)
        throw ListException(ListExceptionCause::ElementNotFound);

    return lastNode;
}

template <typename T>
T List<T>::get(unsigned int index)
{
    return this->getNode(index)->item;
}

template <typename T>
T List<T>::first()
{
    if (this->firstNode == NULL)
        throw ListException(ListExceptionCause::ElementsNotFound);

    return this->firstNode->item;
}

template <typename T>
T List<T>::last()
{
    if (this->firstNode == NULL)
        throw ListException(ListExceptionCause::ElementsNotFound);

    ListNode *lastNode = this->firstNode;

    do
    {
        lastNode = lastNode->nextNode;
    }
    while (lastNode->nextNode != NULL);

    return lastNode->item;
}
