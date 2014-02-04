/* dtkPlotViewGrid.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:52:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jul  5 11:15:05 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 42
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTVIEWGRID_H
#define DTKPLOTVIEWGRID_H

#include "dtkPlotSupportExport.h"

#include <QtCore/QObject>

#include <QtGui/QColor>

class dtkPlotView;
class dtkPlotViewGridPrivate;

class DTKPLOTSUPPORT_EXPORT dtkPlotViewGrid : public QObject
{
    Q_OBJECT

public:
     dtkPlotViewGrid(dtkPlotView *parent);
    ~dtkPlotViewGrid(void);

public:
    QColor color(void) const;

    void setColor(const QColor& color);

private:
    dtkPlotViewGridPrivate *d;
};

#endif
