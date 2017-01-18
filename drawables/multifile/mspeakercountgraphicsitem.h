#ifndef MSPEAKERCOUNTGRAPHICSITEM_H
#define MSPEAKERCOUNTGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QStaticText>
#include <QFont>

class MultiTimelineWidget;
class Speaker;

class MSpeakerCountGraphicsItem : public QGraphicsItem
{
public:
    MSpeakerCountGraphicsItem(Speaker *s, const QRectF &trsRect, MultiTimelineWidget *timelineWidget);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    Speaker* getSpeaker() const;

    static void setYCounter(int value);

    QColor getColor() const;

private:
    Speaker *speaker;
    MultiTimelineWidget *timelineWidget;
    QRectF rect, barRect;
    QColor color;
    QString label;
    static QFont font;
    static int yCounter;
};

#endif // MSPEAKERCOUNTGRAPHICSITEM_H
