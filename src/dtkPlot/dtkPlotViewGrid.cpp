/* dtkPlotViewGrid.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:55:56 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jun 20 13:12:27 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 77
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
     dtkPlotViewGridPrivate(dtkPlotView *parent);
    ~dtkPlotViewGridPrivate(void);

public:
    QwtPlot *plot;
};

dtkPlotViewGridPrivate::dtkPlotViewGridPrivate(dtkPlotView *parent) : QwtPlotGrid()
{
    plot = reinterpret_cast<QwtPlot *>(parent->plotWidget());

    attach(plot);
}

dtkPlotViewGridPrivate::~dtkPlotViewGridPrivate(void)
{

}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkPlotViewGrid::dtkPlotViewGrid(dtkPlotView *parent) : QObject(parent), d(new dtkPlotViewGridPrivate(parent))
{
    d->setPen(QPen(Qt::DotLine));
    d->setMajPen(QPen(Qt::gray, 0, Qt::DotLine));
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

void dtkPlotViewGrid::setColor(const QColor& color)
{
    d->setMajPen(QPen(color, 0, Qt::DotLine));
}
