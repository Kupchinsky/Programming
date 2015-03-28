#include <memory>

template <typename T>
Queue<T>::Queue(): firstNode(NULL)
{
}

template <typename T>
Queue<T>::~Queue()
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

template <typename T>
void Queue<T>::add(T newItem)
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

template <typename T>
T Queue<T>::peek()
{
    if (this->firstNode == NULL)
        throw QueueException(QueueExceptionCause::HeadNotFound);

    return this->firstNode->item;
}

template <typename T>
T Queue<T>::poll()
{
    if (this->firstNode == NULL)
        throw QueueException(QueueExceptionCause::HeadNotFound);

    std::unique_ptr<QueueNode> savedNode(this->firstNode);
    this->firstNode = savedNode.get()->nextNode;

    return savedNode.get()->item;
}

template <typename T>
unsigned int Queue<T>::size()
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
