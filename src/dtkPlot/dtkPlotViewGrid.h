/* dtkPlotViewGrid.h --- 
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

#ifndef DTKPLOTVIEWGRID_H
#define DTKPLOTVIEWGRID_H

#include "dtkPlotExport.h"

#include <QtCore/QObject>

class dtkPlotView;
class dtkPlotViewGridPrivate;

class DTKPLOT_EXPORT dtkPlotViewGrid : public QObject
{
    Q_OBJECT

public:
     dtkPlotViewGrid(dtkPlotView *parent);
    ~dtkPlotViewGrid(void);

public:
    void   activate(void);
    void deactivate(void);

private:
    dtkPlotViewGridPrivate *d;
};

#endif
