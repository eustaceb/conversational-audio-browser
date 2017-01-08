#ifndef TURNGRAPHICSITEM_H
#define TURNGRAPHICSITEM_H

#include <QGraphicsItem>

class TimelineWidget;
class Turn;

class TurnGraphicsItem : public QGraphicsItem
{
public:
    TurnGraphicsItem(Turn *t,  TimelineWidget *timelineWidget);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    Turn *getTurn() const;

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event) Q_DECL_OVERRIDE;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) Q_DECL_OVERRIDE;

private:
    Turn *turn;
    TimelineWidget *timelineWidget;

    QRectF rect;
    QColor color;

    static QFont font;
    QString hoverLabel;

    bool hovered;
};

#endif // TURNGRAPHICSITEM_H
