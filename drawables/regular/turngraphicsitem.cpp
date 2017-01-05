#include "turngraphicsitem.h"
#include <QDebug>

QFont TurnGraphicsItem::font = QFont("arial", 16);

TurnGraphicsItem::TurnGraphicsItem(Turn *t, TimelineWidget *timelineWidget)
    :turn(t), timelineWidget(timelineWidget), hovered(false)
{
    setAcceptHoverEvents(true);

    SpeakerGraphicsItem *sg = timelineWidget->getSpeakerGraphics().find(turn->getSpeaker()).value();
    color = sg->getColor();

    qreal width = (t->getEndTime() - t->getStartTime()) * 10;

    // TODO: Fix the hardcoded 200
    rect = QRectF(t->getStartTime() * 10 - 200, sg->boundingRect().y(), width, sg->boundingRect().height());

    hoverLabel = turn->getSpeaker()->getName()
            + " from " + QString::number(turn->getStartTime()) + " to "   + QString::number(turn->getEndTime());
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
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QBrush brush;
    if (turn->isSelected() && turn->getSpeaker()->isFiltered())
        brush = QBrush(color.lighter(200));
    else
        brush = QBrush(color);

    brush.setStyle(Qt::SolidPattern);

    QPen pen = QPen(QColor(0, 0, 0));
    pen.setWidth(0);

    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(rect);

    if (hovered) {
        // TODO: Minor bug when zoom > 8
        qreal scale = timelineWidget->getZoomScale() < 8 ? timelineWidget->getZoomScale() : 8;

        font.setPixelSize(ceil(16 / scale));
        QRectF hoverRect = QRectF(timelineWidget->getCursor().x() + 8 / scale,
                                  timelineWidget->getCursor().y() - (36 / scale),
                                  hoverLabel.length() * 8 / scale, 26 / scale);

        brush = QBrush(QColor(255, 255, 255));

        painter->setBrush(brush);
        painter->drawRect(hoverRect);

        painter->setFont(font);
        painter->drawText(hoverRect, Qt::AlignCenter, hoverLabel);
    }
}

void TurnGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    setZValue(1);
    hovered = true;
    color = color.lighter(120);
    this->update();
}

void TurnGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    setZValue(0);
    hovered = false;
    color = color.darker(120);
    this->update();
}


Turn* TurnGraphicsItem::getTurn() const
{
    return turn;
}
