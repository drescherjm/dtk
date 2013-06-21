/* dtkPlotViewZoomer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:52:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun 19 10:42:15 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 51
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
#include <QtCore/QRectF>

#include <QtGui/QColor>

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

public:
    void setColor(const QColor& color);

public:
    void updateBase(const QRectF& rectf);

public:
    void zoomForward(void);
    void zoomBackward(void);

signals:
    void zoomForwardEnabled(bool);
    void zoomBackwardEnabled(bool);

protected slots:
    void onZoomed(const QRectF&);

private:
    dtkPlotViewZoomerPrivate *d;
};

#endif
