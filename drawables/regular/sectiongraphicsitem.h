#ifndef SECTIONGRAPHICSITEM_H
#define SECTIONGRAPHICSITEM_H

#include <QGraphicsItem>
#include "timelinewidget.h"
#include "data-models/section.h"

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class TimelineWidget;
class Section;

class SectionGraphicsItem : public QGraphicsItem
{
public:
    SectionGraphicsItem(TimelineWidget *timelineWidget);
    SectionGraphicsItem(Section *s, TimelineWidget *timelineWidget);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    Section *getSection() const;
    void setSection(Section *s);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    TimelineWidget *timelineWidget;
    QRectF rect;
    Section *section;
    //QColor color;
};

#endif // SECTIONGRAPHICSITEM_H
