#include "graph.hpp"
#include <QVectorIterator>
#include <QDebug>
#include <QMutableListIterator>

Graph::Graph()
{
}

Graph::~Graph()
{
    this->clear();
}

void Graph::clear()
{
    this->relations.clear();
}

void Graph::addRelation(unsigned int i, unsigned int j, int weight)
{
    if (i == j || !isNodeExists(i))
        return;

    bool result;
    this->getRelation(i, j, &result);

    if (result)
        return;

    GraphRelation newRel;

    newRel.i = i;
    newRel.j = j;
    newRel.weight = weight;

    this->relations << newRel;
}

void Graph::delRelation(unsigned int i, unsigned int j)
{
    QVectorIterator<GraphRelation> iter(this->relations);
    unsigned int _i = 0;

    while (iter.hasNext())
    {
        GraphRelation rel = iter.next();

        if ((rel.i == i && rel.j == j) || (rel.i == j && rel.j == i))
        {
            this->relations.erase(this->relations.begin() + _i);
            break;
        }

        _i++;
    }
}

unsigned int Graph::size()
{
    QListIterator<unsigned int> iter(this->nodes);
    unsigned int size = 0;

    while (iter.hasNext())
        size = std::max(size, iter.next());

    return size + (this->nodes.size() != 0 ? 1 : 0);
}

bool Graph::isRelationsExists(unsigned int i)
{
    QVectorIterator<GraphRelation> iter(this->relations);

    while (iter.hasNext())
    {
        GraphRelation rel = iter.next();

        if (rel.i == i || rel.j == i)
            return true;
    }

    return false;
}

GraphRelation Graph::getRelation(unsigned int i, unsigned int j, bool *result)
{
    QVectorIterator<GraphRelation> iter(this->relations);

    while (iter.hasNext())
    {
        GraphRelation rel = iter.next();

        if ((rel.i == i && rel.j == j) || (rel.i == j && rel.j == i))
        {
            *result = true;
            return rel;
        }
    }

    *result = false;
}

void Graph::loadFromStream(std::istream& ifs)
{
    unsigned int size;
    ifs >> size;

    for (unsigned int i = 1; i <= size; i++)
    {
        unsigned int newNode;
        ifs >> newNode;

        this->nodes << newNode;
    }

    ifs >> size;

    for (unsigned int i = 1; i <= size; i++)
    {
        GraphRelation newRel;
        ifs >> newRel.i >> newRel.j >> newRel.weight;

        this->relations << newRel;
    }
}

void Graph::saveToStream(std::ostream& os)
{
    os << this->nodes.size() << std::endl;
    QListIterator<unsigned int> iter(this->nodes);

    while (iter.hasNext())
        os << iter.next() << std::endl;

    os << this->relations.size() << std::endl;
    QVectorIterator<GraphRelation> iter2(this->relations);

    while (iter2.hasNext())
    {
        GraphRelation rel = iter2.next();
        os << rel.i << " " << rel.j << " " << rel.weight << std::endl;
    }
}

void Graph::printRelations()
{
    qDebug() << "Relations:";

    QVectorIterator<GraphRelation> iter(this->relations);

    while (iter.hasNext())
    {
        GraphRelation rel = iter.next();
        qDebug() << rel.i << " " << rel.j << " " << rel.weight;
    }

    qDebug() << "Nodes:";

    QListIterator<unsigned int> iter2(this->nodes);

    while(iter2.hasNext())
        qDebug() << iter2.next();
}

bool Graph::isNodeExists(unsigned int i)
{
    return this->nodes.contains(i);
}

void Graph::addNode(unsigned int i)
{
    if (isNodeExists(i))
        return;

    this->nodes.append(i);
}

void Graph::delNode(unsigned int i)
{
    if (!isNodeExists(i))
        return;

    QVectorIterator<GraphRelation> iter(this->relations);
    unsigned int _i = 0;

    while (iter.hasNext())
    {
        GraphRelation rel = iter.next();

        if (rel.i == i || rel.j == i)
        {
            this->relations.erase(this->relations.begin() + _i);
            break;
        }

        _i++;
    }

    QMutableListIterator<unsigned int> iter2(this->nodes);

    while(iter2.hasNext())
    {
        if (iter2.next() == i)
        {
            iter2.remove();
            break;
        }
    }
}
