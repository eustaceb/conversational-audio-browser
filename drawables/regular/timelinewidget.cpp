#include "timelinewidget.h"
#include "drawables/regular/sectiongraphicsitem.h"
#include "drawables/regular/speakergraphicsitem.h"

#include <math.h>
#include <QKeyEvent>
#include <QDebug>

TimelineWidget::TimelineWidget(const Transcription &t, QWidget *parent)
    : QGraphicsView(parent), transcription(t), zoomScale(1)
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
    setTransformationAnchor(NoAnchor);
    setDragMode(RubberBandDrag);

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
        QPointF oldp = mapToScene(QPoint(m_originX, m_originY));
        QPointF newp = mapToScene(event->pos());
        QPointF translation = newp - oldp;

        translate(translation.x() / zoomScale, translation.y() / zoomScale);

        m_originX = event->x();
        m_originY = event->y();
    }
}

TimelineWidget::Tool TimelineWidget::getTool() const
{
    return tool;
}

void TimelineWidget::triggerTool()
{
    switch (tool) {
    case HandTool:
        tool = SelectTool;
        break;
    case SelectTool:
        tool = HandTool;
        break;
    default:
        break;
    }
}


void TimelineWidget::itemMoved()
{

}


void TimelineWidget::zoomIn()
{
    zoomScale *= 4;
    scaleView(qreal(1.2));
}

void TimelineWidget::zoomOut()
{
    zoomScale /= 4;
    scaleView(1 / qreal(1.2));
}

void TimelineWidget::keyPressEvent(QKeyEvent *event)
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
