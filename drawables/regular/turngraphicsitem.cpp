#include "turngraphicsitem.h"


TurnGraphicsItem::TurnGraphicsItem(const Turn &t, TimelineWidget *timelineWidget)
    :turn(t), timelineWidget(timelineWidget)
{
    SpeakerGraphicsItem *sg = timelineWidget->getSpeakerGraphics().find(turn.getSpeaker()).value();
    color = sg->getColor();

    qreal width = (t.getEndTime() - t.getStartTime()) * 10;

    // TODO: Fix the hardcoded 200
    rect = QRectF(t.getStartTime() * 10 - 200, sg->boundingRect().y(), width, sg->boundingRect().height());
}

QRectF TurnGraphicsItem::boundingRect() const
{
    return rect;
}

QPainterPath TurnGraphicsItem::shape() const
{
    QPainterPath path;
    path.addRect(rect);
    return path;
}

void TurnGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush = QBrush(color);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->drawRect(rect);

    //painter->setFont(font);
    //painter->setPen(QPen(QColor(255 - color.red(), 255 - color.green(), 255 - color.blue())));
    //painter->drawStaticText(rect.x(), rect.y(), label);
}

Turn TurnGraphicsItem::getTurn() const
{
    return turn;
}
