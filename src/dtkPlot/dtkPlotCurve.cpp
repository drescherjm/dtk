/* dtkPlotCurve.cpp --- 
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 16:09:17 2011 (+0200)
 * Version: $Id$
 * Last-Updated: 2012 Thu Dec 13 15:13:47 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 164
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

#include <float.h>

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

QRectF qMakeRect(qreal xmin, qreal xmax, qreal ymin, qreal ymax);

// /////////////////////////////////////////////////////////////////
// dtkPlotCurvePrivateData
// /////////////////////////////////////////////////////////////////

class dtkPlotCurvePrivateData : public QwtPointSeriesData
{
public:
    void append(const QPointF& point);

    void setData(const QVector<QPointF>& data);
    
public:
    void clear(void);

public:
    QRectF boundingRect(void) const {
        return qMakeRect(xmin, xmax, ymin, ymax);
    }

public:
    qreal xmin, xmax;
    qreal ymin, ymax;
};

void dtkPlotCurvePrivateData::append(const QPointF& data)
{
    this->d_samples << data;

    xmin = qMin(xmin, data.x());
    xmax = qMax(xmax, data.x());
    ymin = qMin(ymin, data.y());
    ymax = qMax(ymax, data.y());
}

void dtkPlotCurvePrivateData::setData(const QVector<QPointF>& data)
{
    foreach (const QPointF& point, data) {
        this->append(point);
    }
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
    data.xmin = DBL_MAX;
    data.xmax = DBL_MIN;
    data.ymin = DBL_MAX;
    data.ymax = DBL_MIN;
}

// /////////////////////////////////////////////////////////////////
// dtkPlotCurve
// /////////////////////////////////////////////////////////////////

dtkPlotCurve::dtkPlotCurve(const QString& title) : QObject(), d(new dtkPlotCurvePrivate(title))
{
    d->setLegendAttribute(QwtPlotCurve::LegendShowLine);
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
    d->itemChanged();
}

void dtkPlotCurve::setName(const QString& name)
{
    d->setTitle(name);
}

void dtkPlotCurve::setAntialiased(bool antiliased)
{
    d->setRenderHint(QwtPlotItem::RenderAntialiased, antiliased);
}

void dtkPlotCurve::setColor(const QColor& color)
{
    d->setPen(color);
}

QString dtkPlotCurve::name(void) const
{
    return d->title().text();
}

QColor dtkPlotCurve::color(void) const
{
    return d->pen().color();
}

qreal dtkPlotCurve::minX(void) const
{
    return d->data.xmin;
}

qreal dtkPlotCurve::maxX(void) const
{
    return d->data.xmax;
}

qreal dtkPlotCurve::minY(void) const
{
    return d->data.ymin;
}

qreal dtkPlotCurve::maxY(void) const
{
    return d->data.ymax;
}

void dtkPlotCurve::setData(const QVector<QPointF>& data)
{
    d->data.setData(data);

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

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

QRectF qMakeRect(qreal xmin, qreal xmax, qreal ymin, qreal ymax)
{
    return QRectF(xmin, ymin, xmax-xmin, ymax-ymin);
}
