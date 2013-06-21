/* dtkPlotViewGrid.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:52:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun 19 10:42:12 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 38
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

#include <QtGui/QColor>

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

public:
    void setColor(const QColor& color);

private:
    dtkPlotViewGridPrivate *d;
};

#endif
