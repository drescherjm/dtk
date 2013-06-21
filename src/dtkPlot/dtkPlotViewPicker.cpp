/* dtkPlotViewPicker.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Jun 10 01:13:40 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jun 20 09:40:35 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotView.h"
#include "dtkPlotViewPicker.h"

#include <qwt_plot.h>
#include <qwt_plot_picker.h>

class dtkPlotViewPickerPrivate : public QwtPlotPicker
{
public:
     dtkPlotViewPickerPrivate(QwtPlotCanvas *canvas);
    ~dtkPlotViewPickerPrivate(void);
};

dtkPlotViewPickerPrivate::dtkPlotViewPickerPrivate(QwtPlotCanvas *canvas) : QwtPlotPicker(canvas)
{
    this->setTrackerMode(QwtPicker::AlwaysOn);
}

dtkPlotViewPickerPrivate::~dtkPlotViewPickerPrivate(void)
{

}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkPlotViewPicker::dtkPlotViewPicker(dtkPlotView *parent) : QObject(parent), d(new dtkPlotViewPickerPrivate(reinterpret_cast<QwtPlot *>(parent->plotWidget())->canvas()))
{
    
}

dtkPlotViewPicker::~dtkPlotViewPicker(void)
{
    delete d;

    d = NULL;
}

void dtkPlotViewPicker::activate(void)
{
    d->setEnabled(true);
}

void dtkPlotViewPicker::deactivate(void)
{
    d->setEnabled(false);
}
