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

void Graph::_dei(unsigned int start, unsigned int end)
{
    unsigned int *x,*t,*h;
    int v;
    unsigned int count = this->size();
    x=new unsigned int [count];//h[i] - вершина, предшествующая i-й вершине на кратчайшем пути
    t=new unsigned int [count];//t[i] - длина кратчайшего пути от вершины s в i
    h=new unsigned int [count];//пройдена/непройдена вершина

    for (unsigned int i=0; i<count; i++)
    {
        t[i]=INT_MAX;
        x[i]=0;
    }

    h[start]=0;
    t[start]=0;
    x[start]=1;
    v=start;

    while(1)// Перебираем все вершины, смежные v, и ищем для них кратчайший путь
    {
        for (unsigned int i=0; i<count; i++)
        {
            bool result;
            GraphRelation rel = this->getRelation(v, i, &result);

            if (!result)
            //if(graf[v][i]==0)
                continue;

            if(x[i]==0 && t[i]>t[v] + rel.weight)
            {
                t[i]=t[v]+rel.weight;
                h[i]=v;
            }
        }

        // Ищем из всех длин некратчайших путей самый короткий
        unsigned int w=INT_MAX;
        v=-1;

        for(unsigned int i=0; i<count; i++)
        {
            if(x[i]==0 && t[i]<w)
            {
                v=i;
                w=t[i];
            }
        }

        if(v==-1)
        {
            //qDebug()<<"net puti iz " << start+1 <<" v " << end+1;
            dei+="Нет пути из ";
            dei+=QString::number(start+1);
            dei+=" в ";
            dei+=QString::number(end+1);
            break;
        }

        if(v==end)
        {
            //qDebug()<<"Put iz " << start+1 <<" v " << end+1 << ": ";
            dei+="Путь из ";
            dei+=QString::number(start+1);
            dei+=" в ";
            dei+=QString::number(end+1);
            dei+=": ";
            unsigned int u =end;
            while(u!=start)
            {
                //qDebug() << " " << u+1;
                path+=QString::number(u+1);
                path+=" ";
                u=h[u];
            }
            //qDebug() << " " << start+1 <<". Dlina puti - " << t[end];

            path+=QString::number(start+1);
            dei+=path;
            dei+=": Длина пути - ";
            dei+=QString::number(t[end]);
            break;
        }
        x[v]=1;
    }
}

QString Graph::getDirectionName(GraphDirection& direction, unsigned int i, unsigned int j)
{
    QString result;

    if (direction == None)
        result = "None";
    else if (direction == Both)
        result = "Both";
    else if (direction == iTo_j)
        result = QString::number(i) + " -> " + QString::number(j);
    else if (direction == jTo_i)
        result = QString::number(i) + " <- " + QString::number(j);

    return result;
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
    if (i == j || !isNodeExists(i) || !isNodeExists(j))
        return;

    bool result;
    this->getRelation(i, j, &result);

    if (result)
        return;

    GraphRelation newRel;

    newRel.i = std::min(i, j);
    newRel.j = std::max(i, j);
    newRel.weight = weight;

    if (newRel.i != i && direction != None && direction != Both) // Значения обменялись местами
    {
        if (direction == iTo_j)
            direction = jTo_i;
        else
            direction = iTo_j;

        qDebug() << "Direction changed!";
    }

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
        qDebug() << rel.i << " " << rel.j << " " << rel.weight << " direction: " << getDirectionName(rel.direction, rel.i, rel.j);
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
