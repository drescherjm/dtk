/* dtkPlotViewPanner.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:55:56 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jun  8 13:44:00 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 28
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotView.h"
#include "dtkPlotViewPanner.h"

#include <qwt_plot.h>
#include <qwt_plot_panner.h>

class dtkPlotViewPannerPrivate : public QwtPlotPanner
{
public:
     dtkPlotViewPannerPrivate(QwtPlotCanvas *canvas);
    ~dtkPlotViewPannerPrivate(void);
};

dtkPlotViewPannerPrivate::dtkPlotViewPannerPrivate(QwtPlotCanvas *canvas) : QwtPlotPanner(canvas)
{

}

dtkPlotViewPannerPrivate::~dtkPlotViewPannerPrivate(void)
{

}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkPlotViewPanner::dtkPlotViewPanner(dtkPlotView *parent) : QObject(parent), d(new dtkPlotViewPannerPrivate(reinterpret_cast<QwtPlot *>(parent->widget())->canvas()))
{
    
}

dtkPlotViewPanner::~dtkPlotViewPanner(void)
{
    delete d;

    d = NULL;
}

void dtkPlotViewPanner::activate(void)
{
    d->setEnabled(true);
}

void dtkPlotViewPanner::deactivate(void)
{
    d->setEnabled(false);
}
