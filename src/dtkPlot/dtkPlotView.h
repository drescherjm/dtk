/* dtkPlotView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Nov 22 10:22:04 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 23 09:42:34 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 15
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTVIEW_H
#define DTKPLOTVIEW_H

#include <QtGui>

#include "dtkPlotExport.h"

class dtkPlotViewPrivate;

class DTKPLOT_EXPORT dtkPlotView : public QGraphicsView
{
    Q_OBJECT

public:
     dtkPlotView(QWidget *parent = 0);
    ~dtkPlotView(void);

private:
    dtkPlotViewPrivate *d;
};

#endif

