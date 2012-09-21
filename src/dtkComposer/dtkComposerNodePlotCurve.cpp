/* dtkComposerNodePlotCurve.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 29 14:40:41 2012 (+0200)
 * Version: $Id$
 * Last-Updated: ven. sept. 21 15:37:12 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 53
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
    dtkComposerTransmitterEmitter<dtkPlotCurve *> emitter_curve;

public:
    dtkPlotCurve *curve;

public:
  bool dirty;
};

dtkComposerNodePlotCurve::dtkComposerNodePlotCurve(void) : QObject(), dtkComposerNodeLeaf(), d(new dtkComposerNodePlotCurvePrivate)
{
    d->curve = new dtkPlotCurve;

    this->appendReceiver(&(d->receiver_x));
    this->appendReceiver(&(d->receiver_y));

    this->appendEmitter(&(d->emitter_curve));

}

dtkComposerNodePlotCurve::~dtkComposerNodePlotCurve(void)
{
    delete d;

    d = NULL;
}

dtkPlotCurve *dtkComposerNodePlotCurve::curve(void)
{
    return d->curve;
}

void dtkComposerNodePlotCurve::run(void)
{
    if(d->receiver_x.isEmpty())
        return;

    if(d->receiver_y.isEmpty())
        return;

    d->curve->append(QPointF(d->receiver_x.data(), d->receiver_y.data()));

    d->emitter_curve.setData(d->curve);

    d->dirty = false;
}
