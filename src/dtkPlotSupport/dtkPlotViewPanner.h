/* dtkPlotViewPanner.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:52:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jun  8 13:09:49 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 21
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

#include <QtCore/QObject>

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
