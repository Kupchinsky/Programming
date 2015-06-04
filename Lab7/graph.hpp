#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <QVector>
#include <QString>
#include <fstream>

struct GraphRelation
{
    unsigned int i, j;
    int weight;
};

class Graph
{
    QVector<GraphRelation> relations;
    QList<unsigned int> nodes;
    QString visitResult;

    void visit(unsigned int, QList<unsigned int>&);
public:
    Graph();
    ~Graph();

    void delRelation(unsigned int, unsigned int);
    void addRelation(unsigned int, unsigned int, int);
    void addNode(unsigned int);
    void delNode(unsigned int);
    QString& visit(unsigned int);

    unsigned int size();
    bool isRelationsExists(unsigned int);
    bool isNodeExists(unsigned int);
    GraphRelation getRelation(unsigned int, unsigned int, bool*);

    void loadFromStream(std::istream&);
    void saveToStream(std::ostream&);
    void clear();
    void printRelations();
};

#endif // GRAPH_HPP
