#ifndef RULER_H
#define RULER_H

#include <QGraphicsItem>

class Ruler : public QGraphicsItem
{
public:
    enum RulerType { Above, Below };

    Ruler(const QRectF &targetRect, const RulerType &type);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    QRectF getRect() const;
    void setRect(const QRectF &value);

private:
    QRectF rect;
    RulerType type;
    bool drawBorder;

    int increment;
    int periodW;
    int textHeight;
};

#endif // RULER_H
