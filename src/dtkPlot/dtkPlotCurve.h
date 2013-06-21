/* dtkPlotCurve.h ---
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 16:05:08 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jun 21 15:17:45 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 61
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
    void setName(const QString& name);
    void setAntialiased(bool antiliased);
    void setColor(const QColor& color);
    void setColorArea(const QColor& color);
    void clear();

    QString name(void) const;
    QColor color(void) const;

    qreal minX(void) const;
    qreal maxX(void) const;
    qreal minY(void) const;
    qreal maxY(void) const;

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

typedef QList<dtkPlotCurve *> dtkPlotCurves;

Q_DECLARE_METATYPE(dtkPlotCurve);
Q_DECLARE_METATYPE(dtkPlotCurve *);

Q_DECLARE_METATYPE(dtkPlotCurves);
Q_DECLARE_METATYPE(dtkPlotCurves *);

#endif
