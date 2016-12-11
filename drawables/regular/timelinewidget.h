#ifndef REGULARTIMELINEWIDGET_H
#define REGULARTIMELINEWIDGET_H

#include <QGraphicsView>
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

    enum Tool { SelectTool, HandTool };


    Tool getTool() const;
    void triggerTool();

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;

    void scaleView(qreal scaleFactor);

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
private:
    AudioTrack *sampleTrack;
    Transcription transcription;
    QGraphicsScene *scene;

    Tool tool;

    int m_originY, m_originX;
    qreal zoomScale;
};

#endif // REGULARTIMELINEWIDGET_H
