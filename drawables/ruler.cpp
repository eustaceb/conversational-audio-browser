#include "ruler.h"

#include <QPainter>

Ruler::Ruler(const QRectF &targetRect, const RulerType &type)
    : increment(10), periodW(100), textHeight(15)
{
    this->type = type;
    drawBorder = false;

    qreal rulerHeight = 30;
    qreal rulerWidth = targetRect.width() + (50 - ((int)targetRect.width() % 50));

    if (type == Above)
        rect = QRectF(targetRect.x(), targetRect.y() - rulerHeight, rulerWidth, rulerHeight);
    else if (type == Below)
        rect = QRectF(targetRect.x(), targetRect.y() + targetRect.height(), rulerWidth, rulerHeight);
}

QRectF Ruler::boundingRect() const
{
    return rect;
}

QPainterPath Ruler::shape() const
{
    QPainterPath path;
    path.addRect(rect);
    return path;
}

void Ruler::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(QColor(0xfaffff));
    // Framing
    if (drawBorder == true) {
        if (type == Above) {
            //painter->drawLine(rect.x() - 5, rect.bottomLeft().y(), rect.topLeft().x() - 5, rect.topLeft().y());
            painter->drawLine(rect.topLeft(), rect.topRight());
            //painter->drawLine(rect.topRight(), rect.bottomRight());
        } else if (type == Below){
            //painter->drawLine(rect.x() - 5, rect.bottomLeft().y(), rect.topLeft().x() - 5, rect.topLeft().y());
            painter->drawLine(rect.bottomLeft(), rect.bottomRight());
            //painter->drawLine(rect.topRight(), rect.bottomRight());
        }
    }

    for (int i = 0; i < rect.width(); i += increment) {
        int x = rect.x() + i;

        if (type == Below) {
            if (!(i % 100)) { // Bigger separators between text
                painter->drawText(x - periodW / 2, rect.bottom() - textHeight, periodW, rect.height(), Qt::AlignHCenter, QString::number(i/10));
                painter->drawLine(x, rect.top(), x, rect.top() + textHeight);
            } else if (!(i % 50)) { // Separators that fall on text
                painter->drawLine(x, rect.top(), x, rect.top() + (rect.height() / 2));
            } else {
                painter->drawLine(x, rect.top(), x, rect.top() + (rect.height() / 4));
            }
        }
        else if (type == Above) {
            if (!(i % 100)) { // Bigger separators between text
                painter->drawText(x - periodW / 2, rect.top(), periodW, rect.height(), Qt::AlignHCenter, QString::number(i/10));
                painter->drawLine(x, rect.bottom(), x, rect.bottom() - textHeight);
            } else if (!(i % 50)) { // Separators that fall on text
                painter->drawLine(x, rect.bottom(), x, rect.bottom() - (rect.height() / 2));
            } else {
                painter->drawLine(x, rect.bottom(), x, rect.bottom() - (rect.height() / 4));
            }
        }
    }
}

QRectF Ruler::getRect() const
{
    return rect;
}

void Ruler::setRect(const QRectF &value)
{
    rect = value;
}
