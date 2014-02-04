/* dtkPlotViewZoomer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:52:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Sep 20 17:19:15 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 54
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTVIEWZOOMER_H
#define DTKPLOTVIEWZOOMER_H

#include "dtkPlotSupportExport.h"

#include <QtCore/QObject>
#include <QtCore/QRectF>

#include <QtGui/QColor>

class dtkPlotView;
class dtkPlotViewZoomerPrivate;

class DTKPLOTSUPPORT_EXPORT dtkPlotViewZoomer : public QObject
{
    Q_OBJECT

public:
     dtkPlotViewZoomer(dtkPlotView *parent);
    ~dtkPlotViewZoomer(void);

public:
    void   activate(void);
    void deactivate(void);

    bool isActivated(void) const;

public:
    QColor color(void) const;

    void setColor(const QColor& color);

public:
    void updateBase(const QRectF& rectf);

private:
    dtkPlotViewZoomerPrivate *d;
};

#endif
