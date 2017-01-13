#ifndef MULTITIMELINEWIDGET_H
#define MULTITIMELINEWIDGET_H

#include <QGraphicsView>
#include <QMap>

class Transcription;

class MultiTimelineWidget : public QGraphicsView
{
    Q_OBJECT
public:
    MultiTimelineWidget(QMap<int, Transcription*> *transcriptions, QWidget *parent = 0);
    ~MultiTimelineWidget();

    void reloadScene();

    QPointF getCursor() const;

    qreal getZoomScale() const;

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

    QMap<int, Transcription*> *transcriptions;

    qreal zoomScale;
    QPointF cursor, origin;
};

#endif // MULTITIMELINEWIDGET_H
