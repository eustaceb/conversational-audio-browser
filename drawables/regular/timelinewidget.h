#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QGraphicsView>
#include <QRubberBand>
#include <QRect>
#include <QMap>

class Transcription;
class Speaker;
class SpeakerGraphicsItem;

class TimelineWidget : public QGraphicsView
{
    Q_OBJECT
public:
    enum Tool { SelectTool, HandTool };

    TimelineWidget(QWidget *parent = 0);
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

signals:
    void mouseMoved();

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
    void scaleView(qreal scaleFactor);
private:
    QGraphicsScene *scene;
    QRubberBand *selectArea;

    Transcription *transcription;

    // Speaker variables
    QMap<Speaker*, SpeakerGraphicsItem*> speakerGraphics;
    qint16 maxSpeakerNameW;

    Tool tool;

    qreal zoomScale;
    QPointF cursor, origin;
};

#endif // TIMELINEWIDGET_H
