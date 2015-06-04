#ifndef CRENDERWIDGET_HPP
#define CRENDERWIDGET_HPP

#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QWidget>
#include "graph.hpp"

class CRenderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CRenderWidget(QWidget *parent = 0);

    Graph* gp;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent*);

private:
    void drawLineWithArrow(QPainter&, QPoint&, QPoint&, GraphDirection&);
};

#endif // CRENDERWIDGET_HPP

