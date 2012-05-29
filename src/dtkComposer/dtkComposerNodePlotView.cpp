/* dtkComposerNodePlotView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 29 14:40:41 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 29 22:59:10 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 51
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodePlotView.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkPlot/dtkPlotCurve.h>
#include <dtkPlot/dtkPlotView.h>

#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewFactory.h>

class dtkComposerNodePlotViewPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkPlotCurve *> receiver_curve;

public:
    dtkPlotView *view;
};

dtkComposerNodePlotView::dtkComposerNodePlotView(void) : QObject(), dtkComposerNodeLeaf(), d(new dtkComposerNodePlotViewPrivate)
{
    d->view = NULL;

    this->appendReceiver(&(d->receiver_curve));

    connect(this, SIGNAL(runned()), this, SLOT(onRun()));
}

dtkComposerNodePlotView::~dtkComposerNodePlotView(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodePlotView::run(void)
{
    emit runned();

    qApp->processEvents();
}

void dtkComposerNodePlotView::onRun(void)
{
    if(d->receiver_curve.isEmpty())
        return;

    if(!d->view)
        d->view = dynamic_cast<dtkPlotView *>(dtkAbstractViewFactory::instance()->create("dtkPlotView"));

    if(!d->view)
        return;

    (*(d->view)) << d->receiver_curve.data();
    
    d->view->update();
}
