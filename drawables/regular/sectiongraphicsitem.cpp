#include "sectiongraphicsitem.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include <QTextOption>

SectionGraphicsItem::SectionGraphicsItem(TimelineWidget *timelineWidget)
    : timelineWidget(timelineWidget)
{
    color = QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255);
    //setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

SectionGraphicsItem::SectionGraphicsItem(const Section &s, TimelineWidget *timelineWidget)
    : section(s), timelineWidget(timelineWidget)
{
    color = QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255);
    double adjust = -200;

    this->rect = QRectF(
                section.getStartTime() * 10 + adjust, // x
                -10 + adjust, // y
                (section.getEndTime() - section.getStartTime()) * 10, // w
                30); // h;

    label = QStaticText(section.getTopic().getDesc());
    QTextOption opt;
    opt.setWrapMode(QTextOption::WordWrap);
    label.setTextOption(opt);
    label.setTextWidth(rect.width());

    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);

    //qInfo() << rect.x() << rect.width() << "next -" << rect.x()+rect.width();
}

QRectF SectionGraphicsItem::boundingRect() const
{
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
    QBrush gradient = QBrush(color);
    //painter->setBrush()
    painter->setBrush(gradient);
    painter->drawRect(rect);
    painter->setPen(QPen(QColor(255 - color.red(), 255 - color.green(), 255 - color.blue())));
    //painter->drawStaticText(rect.x(), rect.y(), label);
    painter->drawText(rect, Qt::TextWrapAnywhere, section.getTopic().getDesc());
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

Section SectionGraphicsItem::getSection() const
{
    return section;
}

void SectionGraphicsItem::setSection(const Section &s)
{
    double adjust = -200;
    section = s;
    //this->section = s;
    this->rect = QRectF(
                section.getStartTime() * 10 + adjust, // x
                -10 + adjust, // y
                (section.getEndTime() - section.getStartTime()) * 10, // w
                30); // h;
}
