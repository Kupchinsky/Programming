#include "graph.hpp"
#include <QVectorIterator>
#include <QDebug>

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
    if (i == j)
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

        if (rel.i == i && rel.j == j)
        {
            this->relations.erase(this->relations.begin() + _i);
            break;
        }

        _i++;
    }
}

void Graph::loadFromStream(std::istream& is)
{
    unsigned int size;
    is >> size;

    for (unsigned int i = 1; i <= size; i++)
    {
        GraphRelation newRel;
        is >> newRel.i >> newRel.j >> newRel.weight;

        this->relations << newRel;
    }
}

unsigned int Graph::size()
{
    QVectorIterator<GraphRelation> iter(this->relations);
    unsigned int size = 0;

    while (iter.hasNext())
    {
        GraphRelation rel = iter.next();
        size = std::max(size, std::max(rel.i + 1, rel.j + 1));
    }

    return size;
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

void Graph::saveToStream(std::ostream& os)
{
    os << this->relations.size() << std::endl;
    QVectorIterator<GraphRelation> iter(this->relations);

    while (iter.hasNext())
    {
        GraphRelation rel = iter.next();
        os << rel.i << " " << rel.j << " " << rel.weight << std::endl;
    }
}

void Graph::printRelations()
{
    QVectorIterator<GraphRelation> iter(this->relations);

    while (iter.hasNext())
    {
        GraphRelation rel = iter.next();
        qDebug() << rel.i << " " << rel.j << " " << rel.weight;
    }
}
