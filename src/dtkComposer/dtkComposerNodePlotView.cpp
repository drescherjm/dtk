/* dtkComposerNodePlotView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 29 14:40:41 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Sep 20 16:23:59 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 124
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
    dtkComposerTransmitterReceiver<dtkPlotCurve> receiver_curve;
    dtkComposerTransmitterReceiver<dtkPlotCurves> receiver_list_curve;
    dtkComposerTransmitterReceiver<QString> receiver_title;
    dtkComposerTransmitterReceiver<QString> receiver_x_axis_label;
    dtkComposerTransmitterReceiver<QString> receiver_y_axis_label;

public:
    dtkPlotView *view;
};

dtkComposerNodePlotView::dtkComposerNodePlotView(void) : QObject(), dtkComposerNodeLeafView(), d(new dtkComposerNodePlotViewPrivate)
{
    d->view = NULL;

    this->appendReceiver(&(d->receiver_curve));
    this->appendReceiver(&(d->receiver_list_curve));
    this->appendReceiver(&(d->receiver_title));
    this->appendReceiver(&(d->receiver_x_axis_label));
    this->appendReceiver(&(d->receiver_y_axis_label));
}

dtkComposerNodePlotView::~dtkComposerNodePlotView(void)
{
    if (d->view)
        delete d->view;

    d->view = NULL;

    delete d;

    d = NULL;
}

dtkAbstractView *dtkComposerNodePlotView::view(void)
{
    return d->view;
}

void dtkComposerNodePlotView::run(void)
{
    if(!d->view)
	d->view = reinterpret_cast<dtkPlotView *>(dtkAbstractViewFactory::instance()->create("dtkPlotView"));

    if (d->receiver_curve.isEmpty() && d->receiver_list_curve.isEmpty()) {
        dtkWarn() << "no curve speficied!";
        return;
    }

    if(!d->view)
        return;

    d->view->clear();

    foreach(dtkPlotCurve *curve, d->receiver_curve.allData()) {
        if (curve) {
            (*(d->view)) << curve;
        }
    }

    foreach(dtkPlotCurves *curves, d->receiver_list_curve.allData()) {
        foreach(dtkPlotCurve *curve, *curves) {
            if (curve) {
                (*(d->view)) << curve;
            }
        }
    }

    if (!d->receiver_title.isEmpty())
        d->view->setTitle(*d->receiver_title.data());

    if(!d->receiver_x_axis_label.isEmpty())
        d->view->setAxisTitleX(*d->receiver_x_axis_label.data());

    if(!d->receiver_y_axis_label.isEmpty())
        d->view->setAxisTitleY(*d->receiver_y_axis_label.data());

    d->view->updateAxes();
    d->view->update();
}
