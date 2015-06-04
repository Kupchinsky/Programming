#include "crenderwidget.hpp"
#include <cmath>
#include <QDebug>

CRenderWidget::CRenderWidget(QWidget *parent) :
    QWidget(parent)
{
}

void CRenderWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.save();

    double f = 0;
    const unsigned int
            size = this->gp->size(),
            textr = 9,
            textadjust = 15,
            r = size * 12,
            adjustx = (this->width() - 50) * 0.5,
            adjusty = (this->height() - 50) * 0.5;
    QPoint* coords = new QPoint[size];

    this->gp->printRelations();
    qDebug() << "size: " << size;

    for (unsigned int i = 0; i < size; i++, f += 360 / size)
    {
        if (!this->gp->isNodeExists(i))
            continue;

        const double
                _angle = f * 3.14 / 180,
                _cos = cos(_angle),
                _sin = sin(_angle);

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
        if (!this->gp->isRelationsExists(i))
            continue;

        for (unsigned int j = 0; j < size; j++)
        {
            if (j + 1 > i)
                continue;

            bool result;
            this->gp->getRelation(i, j, &result);

            if (!result)
                continue;

            QPoint &p1 = coords[i], &p2 = coords[j];

            qDebug() << "get coords of " << i << ", " << j << ": (" << p1.x() << ", " << p1.y() << ")" << ", (" << p2.x() << ", " << p2.y() << ")";

            QLine line(p1.x(), p1.y(), p2.x(), p2.y());
            painter.drawLine(line);
        }
    }

    delete[] coords;

    painter.restore();

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
