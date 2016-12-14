#ifndef TURNGRAPHICSITEM_H
#define TURNGRAPHICSITEM_H

#include <QGraphicsItem>
#include "data-models/turn.h"
#include "drawables/regular/timelinewidget.h"

class TimelineWidget;

class TurnGraphicsItem : public QGraphicsItem
{
public:
    TurnGraphicsItem(const Turn &t,  TimelineWidget *timelineWidget);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    Turn getTurn() const;

private:
    TimelineWidget *timelineWidget;
    Turn turn;
    QRectF rect;
    QColor color;
};

#endif // TURNGRAPHICSITEM_H
