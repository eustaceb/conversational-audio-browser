#include "mspeakergraphicsitem.h"
#include "multitimelinewidget.h"
#include "data-models/speaker.h"

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
    color = s->getColor();
    label = " " + speaker->getName() + " " + QString::number(speaker->getTotalTurnLength()) + " seconds";
    QFontMetrics fm(font);

    int width;
    if (speaker->getTotalTurnLength() == 0)
        width = 0;
    else if (speaker->getTotalTurnLength() == 1)
        width = 100;
    else
        width = log(speaker->getTotalTurnLength()) * 100;

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
