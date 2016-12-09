#ifndef REGULARTIMELINEWIDGET_H
#define REGULARTIMELINEWIDGET_H

#include <QGraphicsView>
#include "audiotrack.h"
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

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;

    void scaleView(qreal scaleFactor);

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
private:
    //int timerId;
    AudioTrack *sampleTrack;
    Transcription transcription;
    QGraphicsScene *scene;
    int m_originY, m_originX;
};

#endif // REGULARTIMELINEWIDGET_H
