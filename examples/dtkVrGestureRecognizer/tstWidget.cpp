#include "tstWidget.h"

#include <dtkCore/dtkGlobal.h>

#include <dtkVr/dtkVrGestureRecognizer.h>
#include <dtkVr/dtkVrGesturePinch.h>

class tstWidgetPrivate
{
public:
    dtkVrGestureRecognizer *recognizer;

public:
    QColor bg;
};

tstWidget::tstWidget(QWidget *parent) : QWidget(parent), d(new tstWidgetPrivate)
{
    d->recognizer = NULL;
    d->bg = Qt::white;

    this->grabGesture(Qt::PanGesture);
    this->grabGesture(Qt::PinchGesture);
    this->grabGesture(Qt::SwipeGesture);
    this->grabGesture(Qt::CustomGesture);
}

tstWidget::~tstWidget(void)
{
    if (d->recognizer)
        d->recognizer->stopConnection();

    delete d;

    d = NULL;
}

QSize tstWidget::sizeHint(void) const
{
    return QSize(800, 600);
}

void tstWidget::setTracker(QUrl tracker)
{
    d->recognizer = new dtkVrGestureRecognizer(this);
    d->recognizer->startConnection(tracker);
}

bool tstWidget::event(QEvent *event)
{
    qDebug() << __func__ << event->type() << QEvent::Gesture;

    if (event->type() == QEvent::Gesture)
        return gestureEvent(static_cast<QGestureEvent*>(event));

    return QWidget::event(event);
}

bool tstWidget::gestureEvent(QGestureEvent *event)
{
    qDebug() << __func__;

    if (QGesture *swipe = event->gesture(Qt::SwipeGesture))
        swipeGestureEvent(static_cast<QSwipeGesture *>(swipe));
    else if (QGesture *pan = event->gesture(Qt::PanGesture))
        panGestureEvent(static_cast<QPanGesture *>(pan));
    else if (QGesture *pinch = event->gesture(Qt::PinchGesture))
        pinchGestureEvent(static_cast<QPinchGesture *>(pinch));
    else if (QGesture *clear = event->gesture(Qt::CustomGesture))
        clearGestureEvent(static_cast<QGesture *>(clear));

    return true;
}

void tstWidget::panGestureEvent(QPanGesture *event)
{
    Q_UNUSED(event);

    d->bg = Qt::red;

    this->update();
}

void tstWidget::pinchGestureEvent(QPinchGesture *event)
{
    if(dtkVrGesturePinch *pinch = static_cast<dtkVrGesturePinch *>(event)) {

        if(pinch->property("State").toString() == "Started")
            qDebug() << DTK_PRETTY_FUNCTION << "Gesture started";

        if(pinch->property("State").toString() == "Updated")
            qDebug() << DTK_PRETTY_FUNCTION << "Gesture updated";

        if(pinch->property("State").toString() == "Finished")
            qDebug() << DTK_PRETTY_FUNCTION << "Gesture finished";
        
        qDebug() << DTK_PRETTY_FUNCTION << "     scale factor is" << pinch->scaleFactor();
        qDebug() << DTK_PRETTY_FUNCTION << "last scale factor is" << pinch->lastScaleFactor();
        
        d->bg = Qt::green;
        
        this->update();
    } else {
        qDebug() << "Unable to get dtk gesture event";
    }

}

void tstWidget::swipeGestureEvent(QSwipeGesture *event)
{
    Q_UNUSED(event);

    d->bg = Qt::blue;

    this->update();
}

void tstWidget::clearGestureEvent(QGesture *event)
{
    Q_UNUSED(event);

    d->bg = Qt::white;

    this->update();
}

void tstWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this); painter.fillRect(event->rect(), d->bg);
}
