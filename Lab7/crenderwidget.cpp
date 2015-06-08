#include "crenderwidget.hpp"
#include <cmath>
#include <QDebug>

#define Pi 3.14
#define ArrowSize 10

CRenderWidget::CRenderWidget(QWidget *parent) :
    QWidget(parent), graph(new Graph()), scale(1)
{
}

Graph* CRenderWidget::getGraph()
{
    return this->graph.get();
}

void CRenderWidget::setScale(qreal newScale)
{
    this->scale = newScale;
}

qreal CRenderWidget::getScale() const
{
    return scale;
}

void CRenderWidget::drawLineWithArrow(QPainter& painter, QPoint& pI, QPoint& pJ, GraphDirection& direction)
{
    QLineF line(pI, pJ);

    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    painter.drawLine(line);

    if (direction == None)
        return;

    double angle = ::acos(line.dx() / line.length());

    if (line.dy() >= 0)
        angle = 6.28 - angle;

    QPoint *sourcePoint = &pI, *destPoint = &pJ;

    QPointF sourceArrowP1 = *sourcePoint + QPointF(::sin(angle + Pi / 3) * ArrowSize, ::cos(angle + Pi / 3) * ArrowSize);
    QPointF destArrowP1 = *destPoint + QPointF(::sin(angle - Pi / 3) * ArrowSize, ::cos(angle - Pi / 3) * ArrowSize);
    QPointF sourceArrowP2 = *sourcePoint + QPointF(::sin(angle + Pi - Pi / 3) * ArrowSize, ::cos(angle + Pi - Pi / 3) * ArrowSize);
    QPointF destArrowP2 = *destPoint + QPointF(::sin(angle - Pi + Pi / 3) * ArrowSize, ::cos(angle - Pi + Pi / 3) * ArrowSize);

    painter.setBrush(Qt::black);

    if (direction == Both || direction == iTo_j)
        painter.drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);

    if (direction == Both || direction == jTo_i)
        painter.drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}

void CRenderWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.save();
    painter.scale(this->scale, this->scale);

    Graph *pgraph = this->graph.get();
    double f = 0;
    const unsigned int
            size = pgraph->size(),
            textr = 9,
            textadjust = 15,
            r = size * 14,
            adjustx = (this->width() - 50) * 0.5,
            adjusty = (this->height() - 50) * 0.5;

    std::unique_ptr<QPoint[]> coords(new QPoint[size]);

    pgraph->printRelations();
    qDebug() << "size: " << size;

    for (unsigned int i = 0; i < size; i++, f += 360 / size)
    {
        if (!pgraph->isNodeExists(i))
            continue;

        const double
                _angle = f * 3.14 / 180,
                _cos = ::cos(_angle),
                _sin = ::sin(_angle);

        QRect rect(adjustx + (r * _cos), adjusty + (r * _sin), 40, 40);
        QPoint point(rect.x() + 20, rect.y() + 20);

        coords[i].setX(point.x());
        coords[i].setY(point.y());

        qDebug() << "set coords of " << i << ": " << coords[i].x() << ", " << coords[i].y();

        QRect pointRect(point.x() - 1, point.y() - 1, 2, 2);

        painter.drawRect(pointRect);
        painter.setBrush(Qt::yellow);
        painter.drawEllipse(rect);

        rect.adjust(textadjust + (_cos * textr), textadjust + (_sin * textr), 0, 0);
        painter.drawText(rect, QString::number(i));
    }

    for (unsigned int i = 0; i < size; i++)
    {
        if (!pgraph->isRelationsExists(i))
            continue;

        for (unsigned int j = 0; j < size; j++)
        {
            if (j + 1 > i)
                continue;

            bool result;
            GraphRelation rel = pgraph->getRelation(i, j, &result);

            if (!result)
                continue;

            QPoint &p1 = coords[i], &p2 = coords[j], p3 = QPoint((p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2);

            painter.drawText(p3, QString::number(rel.weight));

            this->drawLineWithArrow(painter, p1, p2, rel.direction);
        }
    }

    painter.restore();

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
