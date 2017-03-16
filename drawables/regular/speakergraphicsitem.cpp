#include "speakergraphicsitem.h"
#include "timelinewidget.h"
#include "data-models/speaker.h"

int SpeakerGraphicsItem::heightCounter = 0;
QFont SpeakerGraphicsItem::font = QFont("times", 18);

namespace {
   unsigned const short elementH = 30;
   unsigned const short vSpacing = 10;
   unsigned const short scaleW = 15;
   const short leftMargin = -350;
   const short topMargin = -200;
}

SpeakerGraphicsItem::SpeakerGraphicsItem(Speaker *s, TimelineWidget *timelineWidget)
    : speaker(s), timelineWidget(timelineWidget)
{
    color = s->getColor();

    this->rect = QRectF(0 + leftMargin, // x
                heightCounter + topMargin, // y
                timelineWidget->getMaxSpeakerNameW() * scaleW, // w
                elementH); // h;

    heightCounter += elementH + vSpacing;

    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void SpeakerGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QBrush brush = QBrush(color);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->drawRect(rect);

    painter->setFont(font);
    painter->setPen(QPen(QColor(255 - color.red(), 255 - color.green(), 255 - color.blue())));

    painter->drawText(rect, Qt::AlignCenter, speaker->getName());
}

QRectF SpeakerGraphicsItem::boundingRect() const
{
    return rect;
}

QPainterPath SpeakerGraphicsItem::shape() const
{
    QPainterPath path;
    path.addRect(rect);
    return path;
}

QColor SpeakerGraphicsItem::getColor() const
{
    return color;
}

void SpeakerGraphicsItem::setHeightCounter(int value)
{
    heightCounter = value;
}

Speaker *SpeakerGraphicsItem::getSpeaker() const
{
    return speaker;
}

