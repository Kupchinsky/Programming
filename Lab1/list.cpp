#include "list.hpp"

List::List(ListNode *_firstNode): firstNode(_firstNode), notClear(false)
{
}

List::List(): firstNode(NULL), notClear(false)
{
}

List::~List()
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

List::ListNode* List::getFirstNode()
{
    return this->firstNode;
}

void List::pushFirst(_LIST_TYPE newItem)
{
    ListNode *newNode = new ListNode;

    newNode->item = newItem;
    newNode->nextNode = this->firstNode;

    this->firstNode = newNode;
}

void List::deleteFirst()
{
    if (this->firstNode == NULL)
        throw ListException(ListExceptionCause::ElementsNotFound);

    ListNode *nextNode = this->firstNode->nextNode;

    delete this->firstNode;
    this->firstNode = nextNode;
}

void List::pushLast(_LIST_TYPE newItem)
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

void List::deleteLast()
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

unsigned int List::calculateSize()
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

unsigned int List::calculateSizeRecursive()
{
    return this->_calculateSizeRecursive(*this->firstNode);
}

unsigned int List::_calculateSizeRecursive(ListNode current)
{
    return (current.nextNode == NULL ? 1 : this->_calculateSizeRecursive(*current.nextNode) + 1);
}

void List::deleteMostGreaterNode()
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

void List::swapNodes(unsigned int index1, unsigned int index2)
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

List* List::mergeLists(List *secondList)
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

void List::deleteNode(ListNode* node)
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

void List::print(std::ostream *os)
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

void List::noClear()
{
    this->notClear = true;
}

List::ListNode* List::getNode(unsigned int index)
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

_LIST_TYPE List::get(unsigned int index)
{
    return this->getNode(index)->item;
}

_LIST_TYPE List::first()
{
    if (this->firstNode == NULL)
        throw ListException(ListExceptionCause::ElementsNotFound);

    return this->firstNode->item;
}

_LIST_TYPE List::last()
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
