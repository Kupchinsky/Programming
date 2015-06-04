#ifndef CRENDERWIDGET_HPP
#define CRENDERWIDGET_HPP

#include <QBrush>
#include <QPen>
#include <QPixmap>
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
    QPixmap pixmap;
};

#endif // CRENDERWIDGET_HPP

