#include "sectiongraphicsitem.h"
#include "data-models/topic.h"

QFont SectionGraphicsItem::font = QFont("times", 18);

namespace {
   unsigned const short elementH = 460;
   unsigned const short scaleW = 10;
   const short leftMargin = -200;
   const short topMargin = -210;
}


SectionGraphicsItem::SectionGraphicsItem(Section *s, TimelineWidget *timelineWidget)
    : section(s), timelineWidget(timelineWidget)
{
    color = QColor(qrand() % 255, qrand() % 255, qrand() % 255, 255);
    textColor = QColor(255 - color.red(), 255 - color.green(), 255 - color.blue(), 100);

    if (color.lightness() > 127)
        textColor = textColor.darker(200);
    else
        textColor = textColor.lighter(200);

    this->rect = QRectF(
                section->getStartTime() * scaleW + leftMargin, // x
                topMargin, // y
                (section->getEndTime() - section->getStartTime()) * scaleW, // w
                elementH); // h;

    QFontMetrics metrics(font);
    int repeat = rect.width() / metrics.width(section->getTopic()->getDesc());

    label = QStaticText((section->getTopic()->getDesc() + " ").repeated(repeat + 1));

    setAcceptHoverEvents(true);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

QRectF SectionGraphicsItem::boundingRect() const
{
    return rect;
}

QPainterPath SectionGraphicsItem::shape() const
{
    QPainterPath path;
    path.addRect(rect);
    return path;
}

void SectionGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QBrush brush = QBrush(color);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->drawRect(rect);

    painter->setFont(font);
    painter->setPen(QPen(textColor));
    painter->drawStaticText(rect.x(), rect.y(), label);
    painter->drawStaticText(rect.x(), rect.y() + rect.height() - 25, label);
}


void SectionGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    textColor.setAlpha(255);
    this->update();
}

void SectionGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    textColor.setAlpha(100);
    this->update();
}


Section* SectionGraphicsItem::getSection() const
{
    return section;
}
