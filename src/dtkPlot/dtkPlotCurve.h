/* dtkPlotCurve.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 16:05:08 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jul  5 14:20:18 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 21
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTCURVE_H
#define DTKPLOTCURVE_H

#include <QtCore>

class dtkPlotCurvePrivate;

class dtkPlotCurve : public QObject
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
