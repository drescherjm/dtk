/* dtkPlotCurve.h ---
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 16:05:08 2011 (+0200)
 * Version: $Id$
 * Last-Updated: ven. oct. 12 11:57:48 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 47
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
    QVector<QPointF>&  data(void);

public:
    QString description(void);

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
