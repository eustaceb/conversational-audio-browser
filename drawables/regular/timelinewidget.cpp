#include "timelinewidget.h"
#include "drawables/regular/sectiongraphicsitem.h"
#include "drawables/regular/speakergraphicsitem.h"

#include <math.h>
#include <QKeyEvent>
#include <QDebug>

TimelineWidget::TimelineWidget(const Transcription &t, QWidget *parent)
    : QGraphicsView(parent), transcription(t), zoomScale(1), cursor(0, 0)
{
    scene = new QGraphicsScene(this);
    // TODO: Change to some indexing for possible optimisation
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    //scene->setSceneRect(-200, -200, 1600, 1600);
    setScene(scene);
    setCacheMode(CacheNone);
    this->setViewportUpdateMode(BoundingRectViewportUpdate);

    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(NoAnchor);

    setDragMode(RubberBandDrag);
    setMouseTracking(true);
    scale(qreal(0.8), qreal(0.8));

    // Setup default tool
    tool = SelectTool;
    this->setCursor(Qt::ArrowCursor);
    selectArea = new QRubberBand(QRubberBand::Rectangle, this);

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

    // Calculate scene rect
    int margin = 100;
    QRectF r = scene->itemsBoundingRect();
    scene->setSceneRect(r.x() - margin, r.y() - margin, r.width() + margin*2, r.height() + margin * 2);

    viewport()->update();
}

void TimelineWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        origin = event->pos();
        if (tool == SelectTool) {
            selectArea->setGeometry(QRect(event->pos(), QSize(0, 0)));
            selectArea->show();
        }
    }
}

void TimelineWidget::mouseMoveEvent(QMouseEvent* event)
{
    cursor = mapToScene(event->pos());
    if (tool == SelectTool) {
        selectArea->setGeometry(QRect(origin.toPoint(), event->pos()).normalized());
    }
    if ((event->buttons() & Qt::LeftButton) && (tool == HandTool))
    {
        QPointF oldp = mapToScene(origin.toPoint());
        QPointF newp = mapToScene(event->pos());
        QPointF translation = newp - oldp;

        translate(translation.x() / zoomScale, translation.y() / zoomScale);

        origin = event->pos();
    }
    viewport()->repaint();
}

void TimelineWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (tool == SelectTool)
        selectArea->hide();
    // determine selection, for example using QRect::intersects()
    // and QRect::contains().
}

TimelineWidget::Tool TimelineWidget::getTool() const
{
    return tool;
}

void TimelineWidget::setTool(const Tool &t)
{
    tool = t;
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

void TimelineWidget::drawForeground(QPainter *painter, const QRectF &rect)
{
    if (tool == IntervalSelectTool) {
        // Draw mouse tracker
        QPoint from(cursor.x(), scene->sceneRect().y());
        QPoint to(cursor.x(), scene->sceneRect().y() + scene->sceneRect().height());
        painter->drawLine(from, to);
    }
}


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
