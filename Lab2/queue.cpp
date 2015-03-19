#include "queue.hpp"
#include <memory>

Queue::Queue(): firstNode(NULL)
{
}

Queue::~Queue()
{
    if (this->firstNode == NULL)
        return;

    QueueNode *currentNode = this->firstNode;

    do
    {
        QueueNode *nextNode = currentNode->nextNode;

        delete currentNode;
        currentNode = nextNode;
    }
    while (currentNode != NULL);
}

void Queue::add(_QUEUE_TYPE newItem)
{
    QueueNode *lastNode = this->firstNode;

    if (lastNode != NULL)
    {
        for (; lastNode->nextNode != NULL; lastNode = lastNode->nextNode)
        {
        }
    }

    QueueNode *newNode = new QueueNode;

    newNode->item = newItem;
    newNode->nextNode = NULL;

    if (lastNode != NULL)
        lastNode->nextNode = newNode;
    else
        this->firstNode = newNode;
}

_QUEUE_TYPE Queue::peek()
{
    if (this->firstNode == NULL)
        throw QueueException(QueueExceptionCause::HeadNotFound);

    return this->firstNode->item;
}

_QUEUE_TYPE Queue::poll()
{
    if (this->firstNode == NULL)
        throw QueueException(QueueExceptionCause::HeadNotFound);

    std::unique_ptr<QueueNode> savedNode(this->firstNode);
    this->firstNode = savedNode.get()->nextNode;

    return savedNode.get()->item;
}

unsigned int Queue::size()
{
    if (this->firstNode == NULL)
        return 0;

    QueueNode *currentNode = this->firstNode;
    unsigned int returnSize = 0;

    do
    {
        returnSize++;
        currentNode = currentNode->nextNode;
    }
    while (currentNode != NULL);

    return returnSize;
}
