/* dtkPlotCurve.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 16:05:08 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 16 12:30:25 2012 (+0200)
 *           By: tkloczko
 *     Update #: 22
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTCURVE_H
#define DTKPLOTCURVE_H

#include "dtkPlotExport.h"

#include <QtCore>

class dtkPlotCurvePrivate;

class DTKPLOT_EXPORT dtkPlotCurve : public QObject
{
    Q_OBJECT

public:
     dtkPlotCurve(const QString& title = QString());
    ~dtkPlotCurve(void);

    void setAntialiased(bool antiliased);
    void setColor(const QColor& color);
    void setData(const QVector<QPointF>& data);

signals:
    void updated(void);

private:
    friend class dtkPlotView;

private:
    dtkPlotCurvePrivate *d;
};

#endif
