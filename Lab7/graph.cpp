#include "graph.hpp"
#include <QVectorIterator>
#include <QDebug>

void Graph::createRelationNode()
{
    GraphRelationsNode *newNode = new GraphRelationsNode();
    this->relations.append(newNode);
}

Graph::Graph()
{
}

Graph::~Graph()
{
    QVectorIterator<GraphRelationsNode*> iter(this->relations);

    while (iter.hasNext())
        delete iter.next();
}

void Graph::setRelation(unsigned int node1, unsigned int node2, unsigned int weight)
{
    int i_max = std::max(node1, node2) + 1;

    if (this->relations.size() < i_max)
    {
        while (this->relations.size() != i_max)
            createRelationNode();
    }

    GraphRelationsNode* np1 = this->relations.at(node1);

    np1->resize(node2 + 1);
    (*np1)[node2] = weight;

    GraphRelationsNode* np2 = this->relations.at(node2);

    np2->resize(node1 + 1);
    (*np2)[node1] = weight;
}

GraphRelations Graph::getRelations() const
{
    return this->relations;
}
