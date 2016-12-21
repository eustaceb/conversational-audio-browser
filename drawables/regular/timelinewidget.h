#ifndef REGULARTIMELINEWIDGET_H
#define REGULARTIMELINEWIDGET_H

#include <QGraphicsView>
#include <QRubberBand>
#include <QRect>
#include <QMap>

#include "transcription.h"
#include "drawables/ruler.h"
#include "drawables/regular/speakergraphicsitem.h"

class AudioTrack;
class Transcription;
class SpeakerGraphicsItem;

class TimelineWidget : public QGraphicsView
{
    Q_OBJECT

public:
    enum Tool { SelectTool, HandTool, InspectTool };

    TimelineWidget(Transcription *t, QWidget *parent = 0);
    ~TimelineWidget();

    void setTranscription(Transcription *t);

    void reloadScene();

    void itemMoved();

    Tool getTool() const;
    void setTool(const Tool &t);

    // @TODO: Think whether this is a good idea - consider having a ptr to SpeakerGraphicsItem in Speaker
    QMap<Speaker*, SpeakerGraphicsItem*> getSpeakerGraphics() const;

    QPointF getCursor() const;

    qreal getZoomScale() const;

    qint16 getMaxSpeakerNameW() const;

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif
    void drawForeground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;

    void scaleView(qreal scaleFactor);
private:
    QGraphicsScene *scene;
    QRubberBand *selectArea;

    Transcription *transcription;

    // Speaker variables
    QMap<Speaker*, SpeakerGraphicsItem*> speakerGraphics;
    qint16 maxSpeakerNameW;

    Tool tool;

    QPointF cursor, origin;
    qreal zoomScale;
};

#endif // REGULARTIMELINEWIDGET_H
