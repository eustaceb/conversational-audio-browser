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

private:
    Section *section;
    TimelineWidget *timelineWidget;

    QRectF rect;
    QColor color;
    QStaticText label;
    static QFont font;
};

#endif // SECTIONGRAPHICSITEM_H
