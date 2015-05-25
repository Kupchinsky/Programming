#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <QVector>
#include <fstream>

struct GraphRelation
{
    unsigned int i, j;
    int weight;
};

class Graph
{
    QVector<GraphRelation> relations;
public:
    Graph();
    ~Graph();

    void delRelation(unsigned int, unsigned int);
    void addRelation(unsigned int, unsigned int, int);

    unsigned int size();
    bool isRelationsExists(unsigned int);
    GraphRelation getRelation(unsigned int, unsigned int, bool*);

    void loadFromStream(std::istream&);
    void saveToStream(std::ostream&);
    void clear();
    void printRelations();
};

#endif // GRAPH_HPP
