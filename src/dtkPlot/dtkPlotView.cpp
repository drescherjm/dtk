/* dtkPlotView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 17:04:01 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jul  5 14:23:19 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 39
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

class dtkPlotViewPrivate : public QwtPlot
{
public:
};

dtkPlotView::dtkPlotView(QWidget *parent) : QWidget(parent), d(new dtkPlotViewPrivate)
{
    d->canvas()->setFrameStyle(QFrame::NoFrame);
    d->setCanvasBackground(Qt::white);
    d->setStyleSheet("background: white;");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d);
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

void dtkPlotView::setBackgroundColor(const QColor& color)
{
    d->setCanvasBackground(color);
}

dtkPlotView& dtkPlotView::operator<<(dtkPlotCurve *curve)
{
    ((QwtPlotCurve *)(curve->d))->attach((QwtPlot *)d);

    return *(this);
}
