/* dtkPlotViewLegend.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:52:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Sun Jun 10 01:03:52 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 34
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTVIEWLEGEND_H
#define DTKPLOTVIEWLEGEND_H

#include "dtkPlotExport.h"

#include <QtCore/QObject>

class QwtPlotItem;
class dtkPlotView;
class dtkPlotViewLegendPrivate;

class DTKPLOT_EXPORT dtkPlotViewLegend : public QObject
{
    Q_OBJECT

public:
     dtkPlotViewLegend(dtkPlotView *parent);
    ~dtkPlotViewLegend(void);

public:
    void   activate(void);
    void deactivate(void);

protected slots:
    void showItem(QwtPlotItem *item, bool value);

private:
    dtkPlotViewLegendPrivate *d;
};

#endif
