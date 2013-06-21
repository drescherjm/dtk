/* dtkPlotViewLegend.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:52:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jun 20 13:32:22 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 46
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

public:
    void setPosition(int position);

protected slots:
    void showItem(QwtPlotItem *item, bool value);

private:
    dtkPlotViewLegendPrivate *d;
};

#endif
