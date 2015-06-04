#include "graph.hpp"
#include <QVectorIterator>
#include <QDebug>
#include <QMutableListIterator>
#include <QQueue>

Graph::Graph()
{
}

Graph::~Graph()
{
    this->clear();
}

void Graph::clear()
{
    this->nodes.clear();
    this->relations.clear();
}

QString& Graph::visit(unsigned int startNode)
{
    visitResult = "Start visiting...\n";

    QList<unsigned int> list;
    visit(startNode, list);

    qDebug() << visitResult;

    return visitResult;
}

void Graph::visit(unsigned int node, QList<unsigned int>& used)
{
    visitResult += "Visiting ";
    visitResult += QString::number(node);
    visitResult += "\n";

    used << node;

    unsigned int size = this->size();

    for (unsigned int i = 0; i < size; i++)
    {
        if (!this->isNodeExists(i))
            continue;

        bool result;
        this->getRelation(node, i, &result);

        if (result && !used.contains(i))
            visit(i, used);
    }
}

void Graph::addRelation(unsigned int i, unsigned int j, int weight, GraphDirection direction)
{
    if (i == j || !isNodeExists(i))
        return;

    bool result;
    this->getRelation(i, j, &result);

    if (result)
        return;

    GraphRelation newRel;

    newRel.i = std::min(i, j);
    newRel.j = std::max(i, j);
    newRel.weight = weight;
    newRel.direction = direction;

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

        unsigned int direction;
        ifs >> direction;
        newRel.direction = static_cast<GraphDirection>(direction);

        this->relations << newRel;
    }
}

void Graph::saveToStream(std::ostream& os)
{
    // По возрастанию
    qSort(this->nodes.begin(), this->nodes.end());

    os << this->nodes.size() << std::endl;
    QListIterator<unsigned int> iter(this->nodes);

    while (iter.hasNext())
        os << iter.next() << std::endl;

    os << this->relations.size() << std::endl;
    QVectorIterator<GraphRelation> iter2(this->relations);

    while (iter2.hasNext())
    {
        GraphRelation rel = iter2.next();
        os << rel.i << " " << rel.j << " " << rel.weight << " " << rel.direction << std::endl;
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
