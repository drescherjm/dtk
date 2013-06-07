/* dtkPlotViewGrid.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:55:56 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Sun Jun 10 01:03:46 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 64
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotView.h"
#include "dtkPlotViewGrid.h"

#include <qwt_plot.h>
#include <qwt_plot_grid.h>

class dtkPlotViewGridPrivate : public QwtPlotGrid
{
public:
     dtkPlotViewGridPrivate(QwtPlot *plot);
    ~dtkPlotViewGridPrivate(void);
};

dtkPlotViewGridPrivate::dtkPlotViewGridPrivate(QwtPlot *plot) : QwtPlotGrid()
{
    attach(plot);
}

dtkPlotViewGridPrivate::~dtkPlotViewGridPrivate(void)
{

}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkPlotViewGrid::dtkPlotViewGrid(dtkPlotView *parent) : QObject(parent), d(new dtkPlotViewGridPrivate(reinterpret_cast<QwtPlot *>(parent->widget())))
{
    d->setPen(QPen(Qt::DotLine));
    d->setMajPen(QPen(Qt::white, 0, Qt::DotLine));
}

dtkPlotViewGrid::~dtkPlotViewGrid(void)
{
    delete d;

    d = NULL;
}

void dtkPlotViewGrid::activate(void)
{
    d->setVisible(true);
}

void dtkPlotViewGrid::deactivate(void)
{
    d->setVisible(false);
}

