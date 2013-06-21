/* dtkPlotViewZoomer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:55:56 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun 19 16:42:15 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 87
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotView.h"
#include "dtkPlotViewZoomer.h"

#include <qwt_plot.h>
#include <qwt_plot_zoomer.h>

class dtkPlotViewZoomerPrivate : public QwtPlotZoomer
{
public:
     dtkPlotViewZoomerPrivate(QwtPlotCanvas *canvas);
    ~dtkPlotViewZoomerPrivate(void);

public:
    dtkPlotView *view;
};

dtkPlotViewZoomerPrivate::dtkPlotViewZoomerPrivate(QwtPlotCanvas *canvas) : QwtPlotZoomer(canvas)
{
    setMousePattern(QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier);
    setMousePattern(QwtEventPattern::MouseSelect3, Qt::RightButton);
}

dtkPlotViewZoomerPrivate::~dtkPlotViewZoomerPrivate(void)
{

}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkPlotViewZoomer::dtkPlotViewZoomer(dtkPlotView *parent) : QObject(parent), d(new dtkPlotViewZoomerPrivate(reinterpret_cast<QwtPlot *>(parent->plotWidget())->canvas()))
{
    d->view = parent;

    //connect(d, SIGNAL(zoomed(const QRectF &)), this, SLOT(onZoomed(const QRectF&)));

    //connect(this, SIGNAL(zoomForwardEnabled(bool)), parent, SIGNAL(zoomForwardEnabled(bool)));
    //connect(this, SIGNAL(zoomBackwardEnabled(bool)), parent, SIGNAL(zoomBackwardEnabled(bool)));
}

dtkPlotViewZoomer::~dtkPlotViewZoomer(void)
{
    dtkPlotView *parent = reinterpret_cast<dtkPlotView *>(this->parent());

    disconnect(this, SIGNAL(zoomForwardEnabled(bool)), parent, SIGNAL(zoomForwardEnabled(bool)));
    disconnect(this, SIGNAL(zoomBackwardEnabled(bool)), parent, SIGNAL(zoomBackwardEnabled(bool)));

    delete d;

    d = NULL;
}

void dtkPlotViewZoomer::activate(void)
{
    d->setEnabled(true);
}

void dtkPlotViewZoomer::deactivate(void)
{
    d->setEnabled(false);
}

void dtkPlotViewZoomer::zoomForward(void)
{
    d->zoom(1);
}

void dtkPlotViewZoomer::zoomBackward(void)
{
    d->zoom(-1);
}

void dtkPlotViewZoomer::onZoomed(const QRectF&)
{
    int size = d->zoomStack().size();
    int indx = d->zoomRectIndex();

    emit zoomForwardEnabled(indx < size-1);
    emit zoomBackwardEnabled(indx > 0);
}

void dtkPlotViewZoomer::setColor(const QColor& color)
{
    d->setRubberBandPen(QPen(color));
}

void dtkPlotViewZoomer::updateBase(const QRectF& rectf)
{
    d->setZoomBase(rectf);
}
