/* dtkComposerNodePlotCurve.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 29 14:40:41 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mer. févr.  5 10:28:25 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 109
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodePlotCurve.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMathSupport/dtkMath.h>

#include <dtkPlotSupport/dtkPlotCurve.h>

class dtkComposerNodePlotCurvePrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vector_x;
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vector_y;

public:
    dtkComposerTransmitterEmitter<dtkPlotCurve> emitter_curve;

public:
    dtkPlotCurve *curve;
};

dtkComposerNodePlotCurve::dtkComposerNodePlotCurve(void) : QObject(), dtkComposerNodeLeaf(), d(new dtkComposerNodePlotCurvePrivate)
{
    this->appendReceiver(&(d->receiver_vector_x));
    this->appendReceiver(&(d->receiver_vector_y));

    d->curve = new dtkPlotCurve;
    d->emitter_curve.setData(d->curve);
    this->appendEmitter(&(d->emitter_curve));
}

dtkComposerNodePlotCurve::~dtkComposerNodePlotCurve(void)
{
    if (d->curve)
        delete d->curve;

    d->curve = NULL;

    delete d;

    d = NULL;
}

void dtkComposerNodePlotCurve::run(void)
{
    d->curve->clear();

    if (d->receiver_vector_x.isEmpty() && !d->receiver_vector_y.isEmpty()) {
        dtkWarn() << "no vector x speficied in Plot Curve node!";
        return;
    }

    if (!d->receiver_vector_x.isEmpty() && d->receiver_vector_y.isEmpty()) {
        dtkWarn() << "no vector y speficied in Plot Curve node!";
        return;
    }

    if (!d->receiver_vector_x.isEmpty() && !d->receiver_vector_y.isEmpty()) {
        int sizex, sizey;

        const dtkVectorReal *vx = d->receiver_vector_x.constData();
        const dtkVectorReal *vy = d->receiver_vector_y.constData();

        sizex = vx->size();
        sizey = vy->size();

        if (sizex - sizey != 0) {
            dtkWarn() << "size of vector x and y are different in Plot Curve node (size x = " << sizex << ", size y = " << sizey << ")!";
            return;
        }

        QVector<QPointF> data;

        for (int i = 0; i < sizex; i++ ) {
            if (dtkIsInfinite((*vx)[i]) || dtkIsNan((*vx)[i]) || dtkIsInfinite((*vy)[i]) || dtkIsNan((*vy)[i])) {
                dtkWarn() << "Wrong values found in Plot Curve node";
                continue;
            }

            data << QPointF((*vx)[i], (*vy)[i]);
        }

        d->curve->setData(data);
    }
}
