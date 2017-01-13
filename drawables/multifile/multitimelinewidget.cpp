#include "multitimelinewidget.h"

#include "data-models/transcription.h"
#include "data-models/topic.h"
#include "data-models/speaker.h"
#include "data-models/section.h"
#include "data-models/turn.h"

#include "transcriptiongraphicsitem.h"

#include <QMouseEvent>
#include <QWheelEvent>
#include <math.h>


MultiTimelineWidget::MultiTimelineWidget(QMap<int, Transcription *> *transcriptions, QWidget *parent)
    : QGraphicsView(parent), transcriptions(transcriptions), zoomScale(1), cursor(0, 0)
{
    scene = new QGraphicsScene(this);
    // TODO: Change to some indexing for possible optimisation
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(scene);
    setCacheMode(CacheNone);
    setViewportUpdateMode(BoundingRectViewportUpdate);

    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(NoAnchor);

    setDragMode(RubberBandDrag);
    setMouseTracking(true);
    scale(qreal(0.8), qreal(0.8));

    this->setCursor(Qt::OpenHandCursor);

    reloadScene();
}

MultiTimelineWidget::~MultiTimelineWidget()
{
    delete scene;
}

void MultiTimelineWidget::reloadScene()
{
    scene->clear();

    foreach (Transcription *t, (*transcriptions)) {
        scene->addItem(new MultiFile::TranscriptionGraphicsItem(t, this));
        /*foreach (Topic *to, t->getTopics()) {
            foreach (Section *s, to->getSections()) {
                scene->addItem(new Tra(s, this));
            }
        }*/
    }
    viewport()->update();
}

QPointF MultiTimelineWidget::getCursor() const
{
    return cursor;
}

qreal MultiTimelineWidget::getZoomScale() const
{
    return zoomScale;
}

void MultiTimelineWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void MultiTimelineWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void MultiTimelineWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        origin = event->pos();
    }
}

void MultiTimelineWidget::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

    cursor = mapToScene(event->pos());

    if ((event->buttons() & Qt::LeftButton))
    {
        QPointF oldp = mapToScene(origin.toPoint());
        QPointF newp = mapToScene(event->pos());
        QPointF translation = newp - oldp;

        translate(translation.x(), translation.y());

        origin = event->pos();
    }
    // TODO: Do we really need to repaint every time?
    viewport()->repaint();
}

void MultiTimelineWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void MultiTimelineWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

#ifndef QT_NO_WHEELEVENT
void MultiTimelineWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, event->delta() / 240.0));
}
#endif

void MultiTimelineWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.05 || factor > 100)
        return;

    zoomScale *= scaleFactor;

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    scale(scaleFactor, scaleFactor);
    setTransformationAnchor(QGraphicsView::NoAnchor);
}