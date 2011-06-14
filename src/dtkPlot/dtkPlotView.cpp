/* dtkPlotView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 17:04:01 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun  7 18:19:23 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotView.h"

#include <qwt_plot_canvas.h>

class dtkPlotViewPrivate
{
public:
    
};

dtkPlotView::dtkPlotView(QWidget *parent) : QwtPlot(parent), d(new dtkPlotViewPrivate)
{
    this->canvas()->setFrameStyle(QFrame::NoFrame);
}

dtkPlotView::~dtkPlotView(void)
{
    delete d;

    d = NULL;
}
