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

SpeakerGraphicsItem::SpeakerGraphicsItem(const Speaker &s, TimelineWidget *timelineWidget)
    : speaker(s), timelineWidget(timelineWidget)
{
    color = QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255);
    double adjust = -350;

    this->rect = QRectF(0 + adjust, // x
                heightCounter + adjust + 150, // y
                150, // w
                30); // h;

    heightCounter += 30 + 10;

    label = QStaticText(speaker.getName());

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
    painter->drawStaticText(rect.x(), rect.y(), label);
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

QVariant SpeakerGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        timelineWidget->itemMoved();
           break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
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

void SpeakerGraphicsItem::setHeightCounter(int value)
{
    heightCounter = value;
}

Speaker SpeakerGraphicsItem::getSpeaker() const
{
    return speaker;
}

