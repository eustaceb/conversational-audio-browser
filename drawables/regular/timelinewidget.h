#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QGraphicsView>
#include <QRubberBand>
#include <QRect>
#include <QMap>
#include <QMediaPlayer>

class Transcription;
class Speaker;
class SpeakerGraphicsItem;

class TimelineWidget : public QGraphicsView
{
    Q_OBJECT
public:
    TimelineWidget(QWidget *parent = 0);
    ~TimelineWidget();

    void setTranscription(Transcription *t);

    void reloadScene();

    QMap<Speaker*, SpeakerGraphicsItem*> getSpeakerGraphics() const;

    QPointF getCursor() const;

    qreal getZoomScale() const;

    qint16 getMaxSpeakerNameW() const;

signals:
    void mouseMoved();

public slots:
    void zoomIn();
    void zoomOut();
    void syncCheckBox(int value);
    void syncPosition(qint64 pos);
    void playerStateChanged(QMediaPlayer::State playerState);

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif
    void scaleView(qreal scaleFactor);

    virtual void drawForeground(QPainter * painter, const QRectF & rect) Q_DECL_OVERRIDE;
private:
    QGraphicsScene *scene;

    Transcription *transcription;

    // Speaker variables
    QMap<Speaker*, SpeakerGraphicsItem*> speakerGraphics;
    qint16 maxSpeakerNameW;

    // Audio player related variables
    bool sync;
    QMediaPlayer::State playerState;

    qreal zoomScale;
    QPointF cursor, origin;
    qreal markerPos;
};

#endif // TIMELINEWIDGET_H
