#include "mspeakercountgraphicsitem.h"

#include "multitimelinewidget.h"
#include "data-models/speaker.h"

int MSpeakerCountGraphicsItem::yCounter = 0;
QFont MSpeakerCountGraphicsItem::font = QFont("times", 14);

namespace {
   unsigned const short lMargin = 300;
   unsigned const short elementW = 100;
   unsigned const short elementH = 25;
   unsigned const short vSpacing = 10;
}

MSpeakerCountGraphicsItem::MSpeakerCountGraphicsItem(Speaker *s, const QRectF &trsRect, MultiTimelineWidget *timelineWidget)
    : speaker(s), timelineWidget(timelineWidget)
{
    color = QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255);

    int width = speaker->getTurns().length() * 10;
    rect = QRectF(-lMargin - trsRect.width() - width, trsRect.y() + yCounter, width, elementH);

    yCounter += elementH + vSpacing;

    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

QRectF MSpeakerCountGraphicsItem::boundingRect() const
{
    return rect;
}

QPainterPath MSpeakerCountGraphicsItem::shape() const
{
    QPainterPath path;
    path.addRect(rect);
    return path;
}

void MSpeakerCountGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QBrush brush = QBrush(color);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->drawRect(rect);

    painter->setFont(font);
    painter->setPen(QPen(QColor(255 - color.red(), 255 - color.green(), 255 - color.blue())));

    painter->drawText(rect, Qt::AlignCenter, speaker->getName() + " " + QString::number(speaker->getTurns().length()) + " occurences total");

}

Speaker *MSpeakerCountGraphicsItem::getSpeaker() const
{
    return speaker;
}

void MSpeakerCountGraphicsItem::setYCounter(int value)
{
    yCounter = value;
}

QColor MSpeakerCountGraphicsItem::getColor() const
{
    return color;
}
