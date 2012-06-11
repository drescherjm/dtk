/* dtkComposerNodePlotView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 29 14:40:41 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jun  1 12:00:08 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 61
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
    dtkComposerTransmitterReceiver<QString> receiver_x_axis_label;
    dtkComposerTransmitterReceiver<QString> receiver_y_axis_label;

public:
    dtkPlotView *view;
};

dtkComposerNodePlotView::dtkComposerNodePlotView(void) : QObject(), dtkComposerNodeLeaf(), d(new dtkComposerNodePlotViewPrivate)
{
    d->view = NULL;

    this->appendReceiver(&(d->receiver_curve));
    this->appendReceiver(&(d->receiver_x_axis_label));
    this->appendReceiver(&(d->receiver_y_axis_label));

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

    if(!d->receiver_x_axis_label.isEmpty())
        d->view->setAxisTitleX(d->receiver_x_axis_label.data());

    if(!d->receiver_y_axis_label.isEmpty())
        d->view->setAxisTitleY(d->receiver_y_axis_label.data());

    (*(d->view)) << d->receiver_curve.data();
    
    d->view->update();
}
