#ifndef AUDIOTRACK_H
#define AUDIOTRACK_H

#include <QGraphicsItem>
#include "regulartimelinewidget.h"

class RegularTimelineWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class AudioTrack : public QGraphicsItem
{
public:
    AudioTrack(RegularTimelineWidget *timelineWidget);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    RegularTimelineWidget *timelineWidget;
};

#endif // AUDIOTRACK_H
