#ifndef SPEAKERGRAPHICSITEM_H
#define SPEAKERGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QStaticText>
#include <QFont>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class TimelineWidget;
class Speaker;

class SpeakerGraphicsItem : public QGraphicsItem
{
public:
    SpeakerGraphicsItem(Speaker *s, TimelineWidget *timelineWidget);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    Speaker* getSpeaker() const;

    static void setHeightCounter(int value);

    QColor getColor() const;

private:
    Speaker *speaker;
    TimelineWidget *timelineWidget;
    QRectF rect;
    QColor color;
    QStaticText label;
    static QFont font;
    static int heightCounter;
};

#endif // SPEAKERGRAPHICSITEM_H
