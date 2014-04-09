/* dtkPlotViewPanner.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:52:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mer. avril  9 13:25:52 2014 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 22
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTVIEWPANNER_H
#define DTKPLOTVIEWPANNER_H

#include "dtkPlotSupportExport.h"

#include <QObject>

class dtkPlotView;
class dtkPlotViewPannerPrivate;

class DTKPLOTSUPPORT_EXPORT dtkPlotViewPanner : public QObject
{
    Q_OBJECT

public:
     dtkPlotViewPanner(dtkPlotView *parent);
    ~dtkPlotViewPanner(void);

public:
    void   activate(void);
    void deactivate(void);

private:
    dtkPlotViewPannerPrivate *d;
};

#endif
