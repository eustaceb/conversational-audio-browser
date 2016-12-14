#include "turngraphicsitem.h"


TurnGraphicsItem::TurnGraphicsItem(const Turn &t, TimelineWidget *timelineWidget)
    :turn(t), timelineWidget(timelineWidget)
{
    //color =

}

QRectF TurnGraphicsItem::boundingRect() const
{

}

QPainterPath TurnGraphicsItem::shape() const
{

}

void TurnGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

Turn TurnGraphicsItem::getTurn() const
{
    return turn;
}
