#include "transcriptiongraphicsitem.h"

#include "multitimelinewidget.h"
#include "data-models/transcription.h"

QFont TranscriptionGraphicsItem::font = QFont("times", 18);

namespace {
   unsigned const short lMargin = 800;
   unsigned const short elementW = 300;
   unsigned const short speakerH = 25;
   unsigned const short speakerSpacing = 10;
   unsigned const short vSpacing = 30;
}

TranscriptionGraphicsItem::TranscriptionGraphicsItem(Transcription *t, const QRectF &prevRect, MultiTimelineWidget *mtw)
    : transcription(t), multiTimelineWidget(mtw)
{
    color = QColor(200, 200, 200);

    int elementH = transcription->getSpeakers().length() * (speakerH + speakerSpacing) - speakerSpacing;
    rect = QRectF(-lMargin, prevRect.bottom() + vSpacing, elementW, elementH);
}

QRectF TranscriptionGraphicsItem::boundingRect() const
{
    return rect;
}

QPainterPath TranscriptionGraphicsItem::shape() const
{
    QPainterPath path;
    path.addRect(rect);
    return path;
}

void TranscriptionGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QBrush brush = QBrush(color);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->drawRect(rect);

    painter->setFont(font);
    painter->setPen(QPen(QColor(0, 0, 0)));

    painter->drawText(rect, Qt::AlignCenter, transcription->getFilename());
}

Transcription *TranscriptionGraphicsItem::getTranscription() const
{
    return transcription;
}
