#include "regulartimelinewidget.h"
#include <math.h>
#include <QKeyEvent>


RegularTimelineWidget::RegularTimelineWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    // TODO: Change to some indexing for possible optimisation
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    setScene(scene);
    setCacheMode(CacheBackground);
    this->setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));

    sampleTrack = new AudioTrack(this);
    scene->addItem(sampleTrack);
    sampleTrack->setPos(-50, 0);
}

void RegularTimelineWidget::itemMoved()
{

}

void RegularTimelineWidget::shuffle()
{

}

void RegularTimelineWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void RegularTimelineWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void RegularTimelineWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        sampleTrack->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        sampleTrack->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        sampleTrack->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        sampleTrack->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void RegularTimelineWidget::timerEvent(QTimerEvent *event)
{

}

#ifndef QT_NO_WHEELEVENT
void RegularTimelineWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, event->delta() / 240.0));
}
#endif

void RegularTimelineWidget::drawBackground(QPainter *painter, const QRectF &rect)
{

}

void RegularTimelineWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
