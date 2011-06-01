/* dtkPlotView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 17:02:08 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun  1 17:03:54 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
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

class dtkPlotViewPrivate;

class DTKPLOT_EXPORT dtkPlotView : public QWidget
{
    Q_OBJECT

public:
     dtkPlotView(QWidget *parent = 0);
    ~dtkPlotView(void);

private:
    dtkPlotViewPrivate *d;
};

#endif
