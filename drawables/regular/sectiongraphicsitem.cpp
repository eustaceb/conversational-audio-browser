#include "sectiongraphicsitem.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include <QTextOption>
#include <QFontMetrics>

QFont SectionGraphicsItem::font = QFont("times", 18);

SectionGraphicsItem::SectionGraphicsItem(const Section &s, TimelineWidget *timelineWidget)
    : section(s), timelineWidget(timelineWidget)
{
    color = QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255);
    double adjust = -200;

    this->rect = QRectF(
                section.getStartTime() * 10 + adjust, // x
                -10 + adjust, // y
                (section.getEndTime() - section.getStartTime()) * 10, // w
                400); // h;

    QFontMetrics metrics(font);
    int repeat = rect.width() / metrics.width(section.getTopic().getDesc());

    label = QStaticText((section.getTopic().getDesc() + " ").repeated(repeat + 1));

    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
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
    QBrush brush = QBrush(color);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->drawRect(rect);

    painter->setFont(font);
    painter->setPen(QPen(QColor(255 - color.red(), 255 - color.green(), 255 - color.blue())));
    painter->drawStaticText(rect.x(), rect.y(), label);
    painter->drawStaticText(rect.x(), rect.y() + rect.height() - 18, label);
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

