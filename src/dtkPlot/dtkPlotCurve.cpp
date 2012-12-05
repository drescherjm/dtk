/* dtkPlotCurve.cpp --- 
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 16:09:17 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Dec  5 15:53:49 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 132
 */

/* Commentary: 
 *
 */

/* Change log:
 *
 */

#include "dtkPlotCurve.h"

#include <qwt_plot_curve.h>
#include <qwt_series_data.h>

// /////////////////////////////////////////////////////////////////
// dtkPlotCurvePrivateData
// /////////////////////////////////////////////////////////////////

class dtkPlotCurvePrivateData : public QwtPointSeriesData
{
public:
    void append(const QPointF& point);
    
public:
    void clear(void);
};

void dtkPlotCurvePrivateData::append(const QPointF& data)
{
    this->d_samples << data;
}

void dtkPlotCurvePrivateData::clear(void)
{
    this->d_samples.clear();
}

// /////////////////////////////////////////////////////////////////
// dtkPlotCurvePrivate
// /////////////////////////////////////////////////////////////////

class dtkPlotCurvePrivate : public QwtPlotCurve
{
public:
    dtkPlotCurvePrivate(const QString& title = QString());

public:
    dtkPlotCurvePrivateData data;
};

dtkPlotCurvePrivate::dtkPlotCurvePrivate(const QString& title) : QwtPlotCurve(title)
{
    this->setData(&(this->data));
}

// /////////////////////////////////////////////////////////////////
// dtkPlotCurve
// /////////////////////////////////////////////////////////////////

dtkPlotCurve::dtkPlotCurve(const QString& title) : QObject(), d(new dtkPlotCurvePrivate(title))
{

}

dtkPlotCurve::dtkPlotCurve(const dtkPlotCurve& other) : QObject(), d(new dtkPlotCurvePrivate(other.d->title().text()))
{
    d->data.setSamples(other.d->data.samples());
}

dtkPlotCurve::~dtkPlotCurve(void)
{
    delete d;

    d = NULL;
}

dtkPlotCurve& dtkPlotCurve::operator=(const dtkPlotCurve& other)
{
    d->setTitle(other.d->title().text()); 

    d->data.setSamples(other.d->data.samples());

    return *this;
}

void dtkPlotCurve::clear(void)
{
    d->data.clear();
}

void dtkPlotCurve::append(const QPointF& data)
{
    d->data.append(data);
}

void dtkPlotCurve::setAntialiased(bool antiliased)
{
    d->setRenderHint(QwtPlotItem::RenderAntialiased, antiliased);
}

void dtkPlotCurve::setColor(const QColor& color)
{
    d->setPen(color);
}

QColor dtkPlotCurve::color(void)
{
   return d->pen().color();
}

void dtkPlotCurve::setData(const QVector<QPointF>& data)
{
    d->data.setSamples(data);

    // emit updated();
}

const QVector<QPointF> dtkPlotCurve::data(void) const
{
    return d->data.samples();
}

QString  dtkPlotCurve::description(void)
{
    QString string;

    string = "[ " ;
    for (unsigned i = 0; i < d->data.samples().count(); i++) {
        if (i > 0)
            string.append("; ");

        QString stringx = QString("%1").arg(d->data.samples().at(i).x());
        QString stringy = QString("%1").arg(d->data.samples().at(i).y());

        string += "(" +stringx + ", "+ stringy +")";
    }
    string.append(" ]");

    return string;
}
