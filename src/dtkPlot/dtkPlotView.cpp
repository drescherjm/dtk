/* dtkPlotView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 17:04:01 2011 (+0200)
 * Version: $Id$
 * Last-Updated: 2012 Mon Dec 17 09:28:21 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 158
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotCurve.h"
#include "dtkPlotView.h"
#include "dtkPlotViewPanner.h"
#include "dtkPlotViewPicker.h"
#include "dtkPlotViewZoomer.h"
#include "dtkPlotViewGrid.h"
#include "dtkPlotViewLegend.h"

#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_engine.h>

#include <float.h>

class dtkPlotViewPrivate : public QwtPlot
{
public:
    dtkPlotViewPanner *panner;
    dtkPlotViewPicker *picker;
    dtkPlotViewZoomer *zoomer;
    dtkPlotViewGrid *grid;
    dtkPlotViewLegend *legend;

public:
    QList<dtkPlotCurve *> curves;
};

dtkPlotView::dtkPlotView(void) : dtkAbstractView(), d(new dtkPlotViewPrivate())
{
    d->panner = NULL;
    d->picker = NULL;
    d->zoomer = NULL;
    d->grid = NULL;
    d->legend = NULL;

    d->setAxisAutoScale(0, true);
    d->setAxisAutoScale(1, true);

    d->canvas()->setFrameStyle(QFrame::NoFrame);

    d->setCanvasBackground(Qt::white);
}

dtkPlotView::~dtkPlotView(void)
{
    delete d;

    d = NULL;
}

QList<dtkPlotCurve *> dtkPlotView::curves(void)
{
    return d->curves;
}

void dtkPlotView::activatePanning(void)
{
    if(!d->panner)
        d->panner = new dtkPlotViewPanner(this);

    d->panner->activate();
}

void dtkPlotView::updateAxes()
{
    qreal xmin = DBL_MAX;
    qreal xmax = DBL_MIN;
    qreal ymin = DBL_MAX;
    qreal ymax = DBL_MIN;

    foreach(dtkPlotCurve *curve, d->curves) {
      if (((QwtPlotCurve *)(curve->d))->isVisible()) {
        xmin = qMin(xmin, curve->minX());
        xmax = qMax(xmax, curve->maxX());
	ymin = qMin(ymin, curve->minY());
	ymax = qMax(ymax, curve->maxY());
      }
    }

    if (xmin < xmax) {
        this->setAxisScaleX(xmin, xmax);
        this->setAxisScaleY(ymin, ymax);
    }

    d->updateAxes();

    this->update();
}

void dtkPlotView::deactivatePanning(void)
{
    if(!d->panner)
        d->panner = new dtkPlotViewPanner(this);

    d->panner->deactivate();
}

void dtkPlotView::activatePicking(void)
{
    if(!d->picker)
        d->picker = new dtkPlotViewPicker(this);

    d->picker->activate();
}

void dtkPlotView::deactivatePicking(void)
{
    if(!d->picker)
        d->picker = new dtkPlotViewPicker(this);

    d->picker->deactivate();
}

void dtkPlotView::activateZooming(void)
{
    if(!d->zoomer)
        d->zoomer = new dtkPlotViewZoomer(this);

    d->zoomer->activate();
}

void dtkPlotView::deactivateZooming(void)
{
    if(!d->zoomer)
        d->zoomer = new dtkPlotViewZoomer(this);

    d->zoomer->deactivate();
}

void dtkPlotView::zoomForward(void)
{
    if(!d->zoomer)
        d->zoomer = new dtkPlotViewZoomer(this);

    d->zoomer->zoomForward();
}

void dtkPlotView::zoomBackward(void)
{
    d->zoomer->zoomBackward();
}

void dtkPlotView::activateGrid(void)
{
    if(!d->grid)
        d->grid = new dtkPlotViewGrid(this);

    d->grid->activate();

    this->update();
}

void dtkPlotView::deactivateGrid(void)
{
    if(!d->grid)
        d->grid = new dtkPlotViewGrid(this);

    d->grid->deactivate();

    this->update();
}

void dtkPlotView::activateLegend(void)
{
    if(!d->legend)
        d->legend = new dtkPlotViewLegend(this);

    this->update();
}

void dtkPlotView::deactivateLegend(void)
{
    if(d->legend) {
      delete d->legend;
      d->legend = NULL;
    }

    this->update();
}

void dtkPlotView::setAxisTitleX(const QString& title)
{
    d->setAxisTitle(QwtPlot::xBottom, title);
}

void dtkPlotView::setAxisTitleY(const QString& title)
{
    d->setAxisTitle(QwtPlot::yLeft, title);
}

void dtkPlotView::setAxisScaleX(double min, double max)
{
    d->setAxisScale(QwtPlot::xBottom, min, max);
}

void dtkPlotView::setAxisScaleY(double min, double max)
{
    d->setAxisScale(QwtPlot::yLeft, min, max);
}

void dtkPlotView::setAxisScaleX(dtkPlotView::Scale scale)
{
    if(scale == dtkPlotView::Linear)
        d->setAxisScaleEngine(QwtPlot::xBottom, new QwtLinearScaleEngine);
    
    if(scale == dtkPlotView::Logarithmic)
        d->setAxisScaleEngine(QwtPlot::xBottom, new QwtLog10ScaleEngine);
}

void dtkPlotView::setAxisScaleY(dtkPlotView::Scale scale)
{
    if(scale == dtkPlotView::Linear)
        d->setAxisScaleEngine(QwtPlot::yLeft, new QwtLinearScaleEngine);
    
    if(scale == dtkPlotView::Logarithmic)
        d->setAxisScaleEngine(QwtPlot::yLeft, new QwtLog10ScaleEngine);
}

void dtkPlotView::setBackgroundColor(int red, int green, int blue)
{
    this->setBackgroundColor(QColor(red, green, blue));
}

void dtkPlotView::setBackgroundColor(double red, double green, double blue)
{
    this->setBackgroundColor(QColor(red, green, blue));
}

void dtkPlotView::setBackgroundColor(const QColor& color)
{
    d->setCanvasBackground(color);
}

QColor dtkPlotView::BackgroundColor() const
{
    return d->canvasBackground().color();
}

void dtkPlotView::setStyleSheet(const QString& sheet)
{
    d->setStyleSheet(sheet);
}

dtkPlotView& dtkPlotView::operator<<(dtkPlotCurve *curve)
{
    QwtPlotCurve *c = ((QwtPlotCurve *)(curve->d));

    if (c->plot() != d)
        d->curves << curve;

    if (c->plot() != d)
        c->attach((QwtPlot *)d);

    return *(this);
}

void dtkPlotView::update(void)
{
    d->replot();
}

QWidget *dtkPlotView::widget(void)
{
    return d;
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkAbstractView *createPlotView(void)
{
    return new dtkPlotView;
}
