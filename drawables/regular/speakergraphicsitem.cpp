#include "speakergraphicsitem.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include <QTextOption>
#include <QFontMetrics>

int SpeakerGraphicsItem::heightCounter = 0;
QFont SpeakerGraphicsItem::font = QFont("times", 18);

SpeakerGraphicsItem::SpeakerGraphicsItem(Speaker *s, TimelineWidget *timelineWidget)
    : speaker(s), timelineWidget(timelineWidget)
{
    color = QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255);
    double adjust = -350;

    this->rect = QRectF(0 + adjust, // x
                heightCounter + adjust + 150, // y
                timelineWidget->getMaxSpeakerNameW() * 15, // w
                30); // h;

    heightCounter += 30 + 10;

    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void SpeakerGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush = QBrush(color);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->drawRect(rect);

    painter->setFont(font);
    painter->setPen(QPen(QColor(255 - color.red(), 255 - color.green(), 255 - color.blue())));

    painter->drawText(rect, Qt::AlignCenter, speaker->getName());
}

QRectF SpeakerGraphicsItem::boundingRect() const
{
    return rect;
}

QPainterPath SpeakerGraphicsItem::shape() const
{
    QPainterPath path;
    path.addRect(rect);
    return path;
}


void SpeakerGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void SpeakerGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

QColor SpeakerGraphicsItem::getColor() const
{
    return color;
}

void SpeakerGraphicsItem::setHeightCounter(int value)
{
    heightCounter = value;
}

Speaker *SpeakerGraphicsItem::getSpeaker() const
{
    return speaker;
}

