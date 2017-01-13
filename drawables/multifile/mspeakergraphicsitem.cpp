#include "mspeakergraphicsitem.h"
#include "multitimelinewidget.h"
#include "data-models/speaker.h"

int MSpeakerGraphicsItem::yCounter = 0;
QFont MSpeakerGraphicsItem::font = QFont("times", 14);

namespace {
   unsigned const short elementH = 25;
   unsigned const short vSpacing = 10;
}

MSpeakerGraphicsItem::MSpeakerGraphicsItem(Speaker *s, const QRectF &trsRect, MultiTimelineWidget *timelineWidget)
    : speaker(s), timelineWidget(timelineWidget)
{
    color = s->getColor();

    rect = QRectF(trsRect.right(), trsRect.y() + yCounter, speaker->getTotalTurnLength() * 10, elementH);

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
    painter->drawRect(rect);

    painter->setFont(font);
    painter->setPen(QPen(QColor(255 - color.red(), 255 - color.green(), 255 - color.blue())));

    painter->drawText(rect, Qt::AlignCenter, speaker->getName() + " " + QString::number(speaker->getTotalTurnLength()) + "s total");

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
