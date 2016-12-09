#include "timelinewidget.h"
#include "drawables/regular/sectiongraphicsitem.h"
#include "drawables/regular/speakergraphicsitem.h"

#include <math.h>
#include <QKeyEvent>
#include <QDebug>


TimelineWidget::TimelineWidget(const Transcription &t, QWidget *parent)
    : QGraphicsView(parent), transcription(t)
{
    scene = new QGraphicsScene(this);
    // TODO: Change to some indexing for possible optimisation
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    //scene->setSceneRect(-200, -200, 1600, 1600);
    setScene(scene);
    setCacheMode(CacheBackground);
    this->setViewportUpdateMode(BoundingRectViewportUpdate);
    this->setCursor(Qt::OpenHandCursor);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));

    reloadScene();
}

void TimelineWidget::setTranscription(const Transcription &t)
{
    transcription = t;
}

void TimelineWidget::reloadScene()
{
    SpeakerGraphicsItem::setHeightCounter(0);
    scene->clear();
    for (int i = 0; i < transcription.getSections().size(); i++) {
        Section s = transcription.getSections().at(i);
        scene->addItem(new SectionGraphicsItem(s, this));

    }

    for (int i = 0; i < transcription.getSpeakers().size(); i++) {
        Speaker s = transcription.getSpeakers().at(i);
        scene->addItem(new SpeakerGraphicsItem(s, this));
    }
    this->viewport()->update();
}

void TimelineWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Store original position.
        m_originX = event->x();
        m_originY = event->y();
    }
}

void TimelineWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        QPointF oldp = mapToScene(m_originX, m_originY);
        QPointF newp = mapToScene(event->pos());
        QPointF translation = newp - oldp;

        translate(translation.x(), translation.y());

        m_originX = event->x();
        m_originY = event->y();
    }
}


void TimelineWidget::itemMoved()
{

}

void TimelineWidget::shuffle()
{

}

void TimelineWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void TimelineWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void TimelineWidget::keyPressEvent(QKeyEvent *event)
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

void TimelineWidget::timerEvent(QTimerEvent *event)
{

}

#ifndef QT_NO_WHEELEVENT
void TimelineWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, event->delta() / 240.0));
}
#endif

void TimelineWidget::drawBackground(QPainter *painter, const QRectF &rect)
{

}

void TimelineWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
