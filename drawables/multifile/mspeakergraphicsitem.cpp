#include "mspeakergraphicsitem.h"
#include "multitimelinewidget.h"
#include "data-models/speaker.h"
#include "statistics.h"

#include <math.h>

int MSpeakerGraphicsItem::yCounter = 0;
QFont MSpeakerGraphicsItem::font = QFont("times", 14);

namespace {
   unsigned const short elementH = 25;
   unsigned const short vSpacing = 10;
}
#include <QDebug>
MSpeakerGraphicsItem::MSpeakerGraphicsItem(Speaker *s, const QRectF &trsRect, MultiTimelineWidget *timelineWidget)
    : speaker(s), timelineWidget(timelineWidget)
{
    double totalTurnLen = Statistics::turnLength(speaker);

    color = s->getColor();
    label = " " + speaker->getName() + " " + QString::number(totalTurnLen) + " seconds";
    QFontMetrics fm(font);

    int width;
    if (totalTurnLen == 0)
        width = 0;
    else
        width = abs(log(totalTurnLen)) * 100;

    barRect = QRectF(trsRect.right(), trsRect.y() + yCounter, width, elementH);
    rect = barRect.united(QRectF(barRect.topLeft(), QSizeF(fm.width(label), 0)));

    yCounter += elementH + vSpacing;

    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

QRectF MSpeakerGraphicsItem::boundingRect() const
{
    return rect;
}

QPainterPath MSpeakerGraphicsItem::shape() const
{
    QPainterPath path;
    path.addRect(rect);
    return path;
}

void MSpeakerGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QBrush brush = QBrush(color);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->drawRect(barRect);

    painter->setFont(font);
    painter->setPen(QPen(QColor(255 - color.red(), 255 - color.green(), 255 - color.blue())));

    painter->drawText(rect, Qt::AlignLeft, label);

}

Speaker *MSpeakerGraphicsItem::getSpeaker() const
{
    return speaker;
}

void MSpeakerGraphicsItem::setYCounter(int value)
{
    yCounter = value;
}

QColor MSpeakerGraphicsItem::getColor() const
{
    return color;
}
