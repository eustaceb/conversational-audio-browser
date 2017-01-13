#include "transcriptiongraphicsitem.h"

#include "multitimelinewidget.h"
#include "data-models/transcription.h"

int MultiFile::TranscriptionGraphicsItem::yCounter = 0;
QFont MultiFile::TranscriptionGraphicsItem::font = QFont("times", 18);

namespace {
   unsigned const short absoluteMargin = 800;
}

MultiFile::TranscriptionGraphicsItem::TranscriptionGraphicsItem(Transcription *t, MultiTimelineWidget *mtw)
    : transcription(t), multiTimelineWidget(mtw)
{
    color = QColor(200, 200, 200);

    this->rect = QRectF(-absoluteMargin, yCounter, 300, 100);

    yCounter += 150 + 30;
}

QRectF MultiFile::TranscriptionGraphicsItem::boundingRect() const
{
    return rect;
}

QPainterPath MultiFile::TranscriptionGraphicsItem::shape() const
{
    QPainterPath path;
    path.addRect(rect);
    return path;
}

void MultiFile::TranscriptionGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

Transcription *MultiFile::TranscriptionGraphicsItem::getTranscription() const
{
    return transcription;
}
