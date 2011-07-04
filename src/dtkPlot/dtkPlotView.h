/* dtkPlotView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 17:02:08 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun  7 15:11:30 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTVIEW_H
#define DTKPLOTVIEW_H

#include "dtkPlotExport.h"

#include <QtCore>
#include <QtGui>

#include <qwt_plot.h>

class dtkPlotViewPrivate;

class DTKPLOT_EXPORT dtkPlotView : public QwtPlot
{
    Q_OBJECT

public:
     dtkPlotView(QWidget *parent = 0);
    ~dtkPlotView(void);

private:
    dtkPlotViewPrivate *d;
};

#endif
