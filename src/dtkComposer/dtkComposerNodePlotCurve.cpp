/* dtkComposerNodePlotCurve.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 29 14:40:41 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2012 Wed Dec 12 22:02:30 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 60
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

#include <dtkPlot/dtkPlotCurve.h>

class dtkComposerNodePlotCurvePrivate
{
public:
    dtkComposerTransmitterReceiver<qreal> receiver_x;
    dtkComposerTransmitterReceiver<qreal> receiver_y;

public:
    dtkComposerTransmitterEmitter<dtkPlotCurve*> emitter_curve;

public:
    dtkPlotCurve *curve;
};

dtkComposerNodePlotCurve::dtkComposerNodePlotCurve(void) : QObject(), dtkComposerNodeLeaf(), d(new dtkComposerNodePlotCurvePrivate)
{
    this->appendReceiver(&(d->receiver_x));
    this->appendReceiver(&(d->receiver_y));

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

dtkPlotCurve *dtkComposerNodePlotCurve::curve(void)
{
    return d->curve;
}

void dtkComposerNodePlotCurve::run(void)
{
    if (d->receiver_x.isEmpty())
        return;

    if (d->receiver_y.isEmpty())
        return;

    d->curve->append(QPointF(d->receiver_x.data(), d->receiver_y.data()));
}
