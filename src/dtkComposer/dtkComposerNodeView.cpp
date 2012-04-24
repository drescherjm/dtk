/* dtkComposerNodeView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr 24 23:29:24 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 25 01:18:51 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 29
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeView.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkLog/dtkLog.h>

#include <dtkCore>

class dtkComposerNodeViewPrivate
{
public:
    dtkComposerTransmitterReceiver<QString> *receiver_type;

public:
    dtkAbstractView *view;
};

dtkComposerNodeView::dtkComposerNodeView(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeViewPrivate)
{
    d->receiver_type = new dtkComposerTransmitterReceiver<QString>(this);
    d->view = NULL;

    this->appendReceiver(d->receiver_type);
}

dtkComposerNodeView::~dtkComposerNodeView(void)
{
    delete d->receiver_type;

    if (d->view)
        delete d->view;

    delete d;

    d = NULL;
}

void dtkComposerNodeView::run(void)
{
    if (d->receiver_type->isEmpty()) {
        dtkWarn() << "no type speficied in view node!";
        return;
    }

    if(!d->view) {
        d->view = dtkAbstractViewFactory::instance()->create(d->receiver_type->data());
        // d->view->resize(200, 100);
        // d->view->show();
    }

    if (!d->view) {
        dtkWarn() << "no view, abort" <<  d->receiver_type->data();
        return;
    }
}

QString dtkComposerNodeView::type(void)
{
    return "view";
}

QString dtkComposerNodeView::titleHint(void)
{
    return "View";
}

QString dtkComposerNodeView::inputLabelHint(int port)
{
    if(port == 0)
        return "type";

    return dtkComposerNodeLeaf::inputLabelHint(port);
}

QString dtkComposerNodeView::outputLabelHint(int port)
{
    return dtkComposerNodeLeaf::outputLabelHint(port);
}
