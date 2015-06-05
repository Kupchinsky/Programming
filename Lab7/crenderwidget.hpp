#ifndef CRENDERWIDGET_HPP
#define CRENDERWIDGET_HPP

#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QWidget>
#include <memory>
#include "graph.hpp"

class CRenderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CRenderWidget(QWidget *parent = 0);
    Graph *getGraph();

private:
    void drawLineWithArrow(QPainter&, QPoint&, QPoint&, GraphDirection&);
    std::unique_ptr<Graph> graph;

protected:
    void paintEvent(QPaintEvent*);
};

#endif // CRENDERWIDGET_HPP

