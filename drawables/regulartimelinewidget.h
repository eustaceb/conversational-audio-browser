#ifndef REGULARTIMELINEWIDGET_H
#define REGULARTIMELINEWIDGET_H

#include <QGraphicsView>
#include "audiotrack.h"

class AudioTrack;

class RegularTimelineWidget : public QGraphicsView
{
    Q_OBJECT

public:
    RegularTimelineWidget(QWidget *parent = 0);

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

private:
    //int timerId;
    AudioTrack *sampleTrack;
};

#endif // REGULARTIMELINEWIDGET_H
