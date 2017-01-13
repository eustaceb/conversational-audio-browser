#ifndef MSPEAKERGRAPHICSITEM_H
#define MSPEAKERGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QStaticText>
#include <QFont>

class MultiTimelineWidget;
class Speaker;

class MSpeakerGraphicsItem : public QGraphicsItem
{
    public:
        MSpeakerGraphicsItem(Speaker *s, const QRectF &trsRect, MultiTimelineWidget *timelineWidget);

        QRectF boundingRect() const Q_DECL_OVERRIDE;
        QPainterPath shape() const Q_DECL_OVERRIDE;

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

        Speaker* getSpeaker() const;

        static void setYCounter(int value);

        QColor getColor() const;

    private:
        Speaker *speaker;
        MultiTimelineWidget *timelineWidget;
        QRectF rect;
        QColor color;
        QStaticText label;
        static QFont font;
        static int yCounter;
};

#endif // MSPEAKERGRAPHICSITEM_H
