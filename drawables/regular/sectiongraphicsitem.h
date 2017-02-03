#ifndef SECTIONGRAPHICSITEM_H
#define SECTIONGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QStaticText>
#include <QFont>

#include "timelinewidget.h"
#include "data-models/section.h"

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class Topic;
class TimelineWidget;
class Section;

class SectionGraphicsItem : public QGraphicsItem
{
public:
    SectionGraphicsItem(Section *s, TimelineWidget *timelineWidget);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    Section* getSection() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

private:
    Section *section;
    TimelineWidget *timelineWidget;

    QRectF rect;
    QColor color, textColor;
    QStaticText label;
    static QFont font;
};

#endif // SECTIONGRAPHICSITEM_H
