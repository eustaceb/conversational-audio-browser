#include "sectiongraphicsitem.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

SectionGraphicsItem::SectionGraphicsItem(TimelineWidget *timelineWidget)
    : timelineWidget(timelineWidget)
{
    //setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

SectionGraphicsItem::SectionGraphicsItem(Section *s, TimelineWidget *timelineWidget)
    : section(s), timelineWidget(timelineWidget)
{
    double adjust = -200;
    qInfo() << section->getTopic();
    this->rect = QRectF(
                section->getStartTime() + adjust, // x
                -10 + adjust, // y
                (section->getEndTime() - section->getStartTime()), // w
                30); // h;
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

QRectF SectionGraphicsItem::boundingRect() const
{
    //qreal adjust = 2;
    // QRectF(-10 - adjust, -10 - adjust, width + adjust, 30 + adjust);
    return rect;
}

QPainterPath SectionGraphicsItem::shape() const
{
    QPainterPath path;
    path.addRect(rect);
    return path;
}

void SectionGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    //painter->setBrush(Qt::darkBlue);
    QBrush gradient = QBrush(QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255));
    //painter->setBrush()
    painter->setBrush(gradient);
    painter->drawRect(rect);
    /*
     *     painter->setPen(Qt::NoPen);

    brush.setColor(Qt::GlobalColor::darkMagenta);
    painter->setBrush(brush);
    painter->drawRect(rect);
    */
    //painter->drawEllipse(-7, -7, 20, 20);

    /*QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).light(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
    } else {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
    painter->setBrush(gradient);*/

    //painter->setPen(QPen(Qt::black, 0));
    //painter->drawEllipse(-10, -10, 20, 20);
}

QVariant SectionGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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

void SectionGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void SectionGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

Section *SectionGraphicsItem::getSection() const
{
    return section;
}

void SectionGraphicsItem::setSection(Section *s)
{
    double adjust = -200;
    section = s;
    //this->section = s;
    this->rect = QRectF(
                section->getStartTime() * 10 + adjust, // x
                -10 + adjust, // y
                (section->getEndTime() - section->getStartTime()) * 10, // w
                30); // h;
}
