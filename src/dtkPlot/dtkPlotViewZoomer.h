/* dtkPlotViewZoomer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:52:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jun  8 13:08:07 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTVIEWZOOMER_H
#define DTKPLOTVIEWZOOMER_H

#include "dtkPlotExport.h"

#include <QtCore/QObject>

class dtkPlotView;
class dtkPlotViewZoomerPrivate;

class DTKPLOT_EXPORT dtkPlotViewZoomer : public QObject
{
    Q_OBJECT

public:
     dtkPlotViewZoomer(dtkPlotView *parent);
    ~dtkPlotViewZoomer(void);

public:
    void   activate(void);
    void deactivate(void);

private:
    dtkPlotViewZoomerPrivate *d;
};

#endif
