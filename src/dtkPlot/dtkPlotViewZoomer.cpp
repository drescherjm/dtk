/* dtkPlotViewZoomer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:55:56 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jun  8 13:43:19 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 29
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
};

dtkPlotViewZoomerPrivate::dtkPlotViewZoomerPrivate(QwtPlotCanvas *canvas) : QwtPlotZoomer(canvas)
{

}

dtkPlotViewZoomerPrivate::~dtkPlotViewZoomerPrivate(void)
{

}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkPlotViewZoomer::dtkPlotViewZoomer(dtkPlotView *parent) : QObject(parent), d(new dtkPlotViewZoomerPrivate(reinterpret_cast<QwtPlot *>(parent->widget())->canvas()))
{
    
}

dtkPlotViewZoomer::~dtkPlotViewZoomer(void)
{
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
