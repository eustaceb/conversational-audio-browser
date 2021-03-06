#include "timelinewidget.h"
#include "data-models/transcription.h"
#include "data-models/speaker.h"
#include "data-models/topic.h"

#include "drawables/regular/sectiongraphicsitem.h"
#include "drawables/regular/speakergraphicsitem.h"
#include "drawables/regular/turngraphicsitem.h"
#include "drawables/ruler.h"

#include <math.h>
#include <QKeyEvent>
#include <QDebug>

#include <QApplication>
#include <QGraphicsSceneEvent>

TimelineWidget::TimelineWidget(QWidget *parent)
    : QGraphicsView(parent), zoomScale(1), cursor(0, 0), markerPos(-200)
{
    scene = new QGraphicsScene(this);
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

    sync = false;
    playerState = QMediaPlayer::StoppedState;
}

TimelineWidget::~TimelineWidget()
{
    //qDeleteAll(speakerGraphics);
    delete scene;

}

void TimelineWidget::setTranscription(Transcription *t)
{
    transcription = t;
}

void TimelineWidget::reloadScene()
{
    scene->clear();
    if (transcription != 0) {
        SpeakerGraphicsItem::setHeightCounter(0);

        // Find the max speaker name width for appropriate rendering
        maxSpeakerNameW = 0;
        foreach (Speaker *s, transcription->getSpeakers()) {
            if (s->getName().length() > maxSpeakerNameW)
                maxSpeakerNameW = s->getName().length();
        }

        for (int i = 0; i < transcription->getSpeakers().size(); i++) {
            Speaker *s = transcription->getSpeakers().at(i);
            SpeakerGraphicsItem *sg = new SpeakerGraphicsItem(s, this);
            speakerGraphics.insert(s, sg);
            scene->addItem(sg);
        }

        // Ruler start point, the top-left point of the first section
        QRectF sectionsRect(0, 0, 0, 0);

        foreach (Topic *topic, transcription->getTopics()) {
            foreach (Section *s, topic->getSections()) {
                SectionGraphicsItem *sectionItem = new SectionGraphicsItem(s, this);

                for (int i = 0; i < s->getTurns().size(); i++) {
                    Turn *t = s->getTurns().at(i);
                    TurnGraphicsItem *turnItem = new TurnGraphicsItem(t, this);
                    scene->addItem(turnItem);
                }
                // Calculate the biggest rect that surrounds sections for rulers
                sectionsRect = sectionsRect.united(sectionItem->boundingRect());

                scene->addItem(sectionItem);
            }
        }
        // Calculate scene rect
        int margin = 100;
        QRectF r = scene->itemsBoundingRect();
        scene->setSceneRect(r.x() - margin, r.y() - margin, r.width() + margin*2, r.height() + margin * 2);

        // Add rulers
        scene->addItem(new Ruler(sectionsRect, Ruler::Above));
        scene->addItem(new Ruler(sectionsRect, Ruler::Below));
    }
    viewport()->update();
}

void TimelineWidget::mousePressEvent(QMouseEvent* event)
{    //p->show();
    if (event->button() == Qt::LeftButton) {
        origin = event->pos();
    }
}

void TimelineWidget::mouseMoveEvent(QMouseEvent* event)
{
    QGraphicsView::mouseMoveEvent(event);

    cursor = mapToScene(event->pos());
    if (event->buttons() & Qt::LeftButton)
    {
        QPointF oldp = mapToScene(origin.toPoint());
        QPointF newp = mapToScene(event->pos());
        QPointF translation = newp - oldp;

        translate(translation.x(), translation.y());

        origin = event->pos();
    }
    viewport()->repaint();
    emit mouseMoved();
}

QMap<Speaker *, SpeakerGraphicsItem *> TimelineWidget::getSpeakerGraphics() const
{
    return speakerGraphics;
}


void TimelineWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void TimelineWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void TimelineWidget::syncCheckBox(int value)
{
    if (value == 2)
        sync = true;
    else
        sync = false;
}

void TimelineWidget::syncPosition(qint64 pos)
{
    markerPos = (pos / 100) - 200;
    if (sync) {
        centerOn(QPointF(markerPos, 0));
    }
    viewport()->repaint();
}

void TimelineWidget::playerStateChanged(QMediaPlayer::State playerState)
{
    this->playerState = playerState;
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
    scaleView(pow((qreal)2, event->delta() / 240.0));
}
#endif


void TimelineWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.05 || factor > 100)
        return;

    zoomScale *= scaleFactor;

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    scale(scaleFactor, scaleFactor);
    setTransformationAnchor(QGraphicsView::NoAnchor);
}

void TimelineWidget::drawForeground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawForeground(painter, rect);

    if (playerState == QMediaPlayer::PausedState || playerState == QMediaPlayer::PlayingState) {
        QBrush brush = QBrush(QColor(255, 0, 0));
        painter->setBrush(brush);
        painter->drawRect(markerPos, -210 - 20, -2, 460 + 40);
    }
}

qint16 TimelineWidget::getMaxSpeakerNameW() const
{
    return maxSpeakerNameW;
}

qreal TimelineWidget::getZoomScale() const
{
    return zoomScale;
}

QPointF TimelineWidget::getCursor() const
{
    return cursor;
}
