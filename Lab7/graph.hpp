#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <QVector>

typedef QVector<unsigned int> GraphRelationsNode;
typedef QVector<GraphRelationsNode*> GraphRelations;

class Graph
{
    GraphRelations relations;

    void createRelationNode();
public:
    Graph();
    ~Graph();

    GraphRelations getRelations() const;
    void setRelation(unsigned int, unsigned int, unsigned int);
};

#endif // GRAPH_HPP

