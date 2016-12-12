#ifndef REGULARTIMELINEWIDGET_H
#define REGULARTIMELINEWIDGET_H

#include <QGraphicsView>
#include <QRubberBand>
#include <QRect>
#include "transcription.h"

class AudioTrack;
class Transcription;

class TimelineWidget : public QGraphicsView
{
    Q_OBJECT

public:
    TimelineWidget(const Transcription &t, QWidget *parent = 0);

    void setTranscription(const Transcription &t);

    void reloadScene();

    void itemMoved();

    enum Tool { SelectTool, HandTool, IntervalSelectTool };


    Tool getTool() const;
    void setTool(const Tool &t);

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif
    void drawForeground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;

    void scaleView(qreal scaleFactor);

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
private:
    QGraphicsScene *scene;
    AudioTrack *sampleTrack;
    QRubberBand *selectArea;

    Transcription transcription;

    Tool tool;

    QPointF cursor, origin;
    qreal zoomScale;
};

#endif // REGULARTIMELINEWIDGET_H
