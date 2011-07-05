/* dtkPlotCurve.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 16:09:17 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jul  5 14:17:02 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 30
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotCurve.h"

#include <qwt_plot_curve.h>

// /////////////////////////////////////////////////////////////////
// dtkPlotCurvePrivate
// /////////////////////////////////////////////////////////////////

class dtkPlotCurvePrivate : public QwtPlotCurve
{
public:
    dtkPlotCurvePrivate(const QString& title = QString());
};

dtkPlotCurvePrivate::dtkPlotCurvePrivate(const QString& title) : QwtPlotCurve(title)
{

}

// /////////////////////////////////////////////////////////////////
// dtkPlotCurve
// /////////////////////////////////////////////////////////////////

dtkPlotCurve::dtkPlotCurve(const QString& title) : QObject(), d(new dtkPlotCurvePrivate(title))
{

}

dtkPlotCurve::~dtkPlotCurve(void)
{
    delete d;

    d = NULL;
}

void dtkPlotCurve::setAntialiased(bool antiliased)
{
    d->setRenderHint(QwtPlotItem::RenderAntialiased, antiliased);
}

void dtkPlotCurve::setColor(const QColor& color)
{
    d->setPen(color);
}

void dtkPlotCurve::setData(const QVector<QPointF>& data)
{
    d->setSamples(data);
}
