/* dtkComposerNodePlotCurveAppendPoint.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 29 14:40:41 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mer. févr.  5 10:28:53 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 97
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodePlotCurveAppendPoint.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkPlotSupport/dtkPlotCurve.h>

class dtkComposerNodePlotCurveAppendPointPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkPlotCurve> receiver_curve;
    dtkComposerTransmitterReceiver<qreal> receiver_x;
    dtkComposerTransmitterReceiver<qreal> receiver_y;

public:
    dtkComposerTransmitterEmitter<dtkPlotCurve> emitter_curve;

public:
    dtkPlotCurve *curve;
};

dtkComposerNodePlotCurveAppendPoint::dtkComposerNodePlotCurveAppendPoint(void) : QObject(), dtkComposerNodeLeaf(), d(new dtkComposerNodePlotCurveAppendPointPrivate)
{
    this->appendReceiver(&(d->receiver_curve));
    this->appendReceiver(&(d->receiver_x));
    this->appendReceiver(&(d->receiver_y));

    this->appendEmitter(&(d->emitter_curve));
}

dtkComposerNodePlotCurveAppendPoint::~dtkComposerNodePlotCurveAppendPoint(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodePlotCurveAppendPoint::run(void)
{
    if (d->receiver_curve.isEmpty()) {
        dtkWarn() << "no curve speficied in Plot Curve Append Point node!";
        return;
    }

    if (d->receiver_x.isEmpty())
        return;

    if (d->receiver_y.isEmpty())
        return;

    dtkPlotCurve *curve = d->receiver_curve.data();

    if (!curve) {
        dtkWarn() << "no curve speficied in Plot Curve Append Point node!";
        return;
    }

    curve->append(QPointF(*d->receiver_x.data(), *d->receiver_y.data()));

    d->emitter_curve.setData(curve);
}
