/* dtkPlotCurve.h ---
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 16:05:08 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 29 15:11:30 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 30
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
     dtkPlotCurve(const dtkPlotCurve& other);
    ~dtkPlotCurve(void);

public:
    void append(const QPointF& data);

public:
    void setAntialiased(bool antiliased);
    void setColor(const QColor& color);
    QColor color(void);

    void setData(const QVector<QPointF>& data);

signals:
    void updated(void);

private:
    friend class dtkPlotView;

private:
    dtkPlotCurvePrivate *d;
};

Q_DECLARE_METATYPE(dtkPlotCurve)
Q_DECLARE_METATYPE(dtkPlotCurve *)

#endif
