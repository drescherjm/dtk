/* dtkComposerNodePlotCurve.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 29 14:40:41 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 29 15:08:44 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 41
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
};

dtkComposerNodePlotCurve::dtkComposerNodePlotCurve(void) : QObject(), dtkComposerNodeLeaf(), d(new dtkComposerNodePlotCurvePrivate)
{
    d->curve = NULL;

    this->appendReceiver(&(d->receiver_x));
    this->appendReceiver(&(d->receiver_y));

    this->appendEmitter(&(d->emitter_curve));

    connect(this, SIGNAL(runned()), this, SLOT(onRun()));
}

dtkComposerNodePlotCurve::~dtkComposerNodePlotCurve(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodePlotCurve::run(void)
{
    emit runned();

    qApp->processEvents();
}

void dtkComposerNodePlotCurve::onRun(void)
{
    if(d->receiver_x.isEmpty())
        return;

    if(d->receiver_y.isEmpty())
        return;

    if(!d->curve)
        d->curve = new dtkPlotCurve;
    
    d->curve->append(QPointF(d->receiver_x.data(), d->receiver_y.data()));

    d->emitter_curve.setData(d->curve);
}
