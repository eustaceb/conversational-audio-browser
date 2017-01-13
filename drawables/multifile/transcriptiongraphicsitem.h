#ifndef TRANSCRIPTIONGRAPHICSITEM_H
#define TRANSCRIPTIONGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QStaticText>
#include <QFont>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class Transcription;
class MultiTimelineWidget;

class TranscriptionGraphicsItem : public QGraphicsItem
{
public:
    TranscriptionGraphicsItem(Transcription *t, const QRectF &prevRect, MultiTimelineWidget *mtw);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    Transcription *getTranscription() const;

private:
    Transcription *transcription;
    MultiTimelineWidget *multiTimelineWidget;

    QRectF rect;
    QColor color;
    QStaticText label;
    static QFont font;
};

#endif // TRANSCRIPTIONGRAPHICSITEM_H
