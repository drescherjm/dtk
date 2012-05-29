/* dtkPlotView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 17:04:01 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 29 14:30:16 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 63
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotCurve.h"
#include "dtkPlotView.h"

#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_engine.h>

class dtkPlotViewPrivate : public QwtPlot
{
public:
};

dtkPlotView::dtkPlotView(void) : dtkAbstractView(), d(new dtkPlotViewPrivate())
{
    d->canvas()->setFrameStyle(QFrame::NoFrame);
    d->setCanvasBackground(Qt::white);
}

dtkPlotView::~dtkPlotView(void)
{
    delete d;

    d = NULL;
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

void dtkPlotView::setBackgroundColor(const QColor& color)
{
    d->setCanvasBackground(color);
}

void dtkPlotView::setStyleSheet(const QString& sheet)
{
    d->setStyleSheet(sheet);
}

dtkPlotView& dtkPlotView::operator<<(dtkPlotCurve *curve)
{
    ((QwtPlotCurve *)(curve->d))->attach((QwtPlot *)d);

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
