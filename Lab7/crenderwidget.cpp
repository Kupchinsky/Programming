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
    const int
            size = this->gp->getRelations().size(),
            textr = 9,
            textadjust = 15,
            r = size * 12,
            adjustx = (this->width() - 50) * 0.5,
            adjusty = (this->height() - 50) * 0.5;
    QVector<QPoint> coords;

    for (int i = 0; i < size; i++, f += 360 / size)
    {
        const double
                _angle = f * 3.14 / 180,
                _cos = cos(_angle),
                _sin = sin(_angle);

        QRect rect(adjustx + (r * _cos), adjusty + (r * _sin), 40, 40);
        QPoint point(rect.x() + 20, rect.y() + 20);

        coords.append(point);

        QRect pointRect(point.x() - 1, point.y() - 1, 2, 2);

        painter.drawRect(pointRect);
        painter.drawEllipse(rect);

        rect.adjust(textadjust + (_cos * textr), textadjust + (_sin * textr), 0, 0);
        painter.drawText(rect, QString::number(i));
    }

    for (int i = 0; i < size; i++)
    {
        GraphRelationsNode *node = this->gp->getRelations().at(i);

        for (int j = 0; j < node->size(); j++)
        {
            if (j + 1 > i || node->at(j) == 0)
                continue;

            qDebug() << i << " " << j;

            QPoint p1 = coords.at(i), p2 = coords.at(j);
            QLine line(p1.x(), p1.y(), p2.x(), p2.y());
            painter.drawLine(line);
        }
    }

    painter.restore();

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
