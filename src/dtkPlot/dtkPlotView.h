/* dtkPlotView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Nov 22 10:22:04 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Nov 22 11:12:55 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 11
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

    QBrush backgroundBrush(void) const;

private:
    dtkPlotViewPrivate *d;
};

#endif
