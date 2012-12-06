/* dtkPlotCurve.h ---
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 16:05:08 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Dec  5 15:52:03 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 53
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
    dtkPlotCurve& operator=(const dtkPlotCurve& other);

public:
    void append(const QPointF& data);

public:
    void setAntialiased(bool antiliased);
    void setColor(const QColor& color);
    void clear();

    QColor color(void);

public:
    void setData(const QVector<QPointF>& data);

public:
    const QVector<QPointF> data(void) const;

public:
    QString description(void);

private:
    friend class dtkPlotView;

private:
    dtkPlotCurvePrivate *d;
};

Q_DECLARE_METATYPE(dtkPlotCurve)
Q_DECLARE_METATYPE(dtkPlotCurve *)

#endif
