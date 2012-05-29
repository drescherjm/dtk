/* dtkComposerNodePlotView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 29 14:40:41 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 29 14:46:31 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 29
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

#include <dtkPlot/dtkPlotView.h>

class dtkComposerNodePlotViewPrivate
{
public:
    dtkComposerTransmitterReceiver<double> receiver_x;
    dtkComposerTransmitterReceiver<double> receiver_y;

public:
    dtkPlotView *view;
};

dtkComposerNodePlotView::dtkComposerNodePlotView(void) : QObject(), dtkComposerNodeLeaf(), d(new dtkComposerNodePlotViewPrivate)
{
    d->view = NULL;

    this->appendReceiver(&(d->receiver_x));
    this->appendReceiver(&(d->receiver_y));

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
    if(d->receiver_x.isEmpty())
        return;

    if(d->receiver_y.isEmpty())
        return;

    if(!d->view) {
        d->view = new dtkPlotView;
        d->view->show();
    }
}
